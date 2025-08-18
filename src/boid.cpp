#include "../include/boid.h"
#include "../include/utils.h"
#include "raylib.h"
#include <cmath>
#include <cstdlib>
#include <vector>

float size = 10;
const float MAX_SPEED = 5;
const float MAX_STEERING = 2.5;

void init_movement(int index);

void create_boid(Vector2 pos) {
  boid b;
  b.position = pos;
  b.velocity = {0, 0};
  b.angle = 0;
  b.detection_area = 65.5f;
  b.steering.x = 0;
  b.steering.y = 0;

  boids.push_back(b);
  int arr_len = boids.size();

  init_movement(arr_len - 1);
}

void render_boid(boid b) {
  Vector2 v1 = {b.position.x, b.position.y - size};
  Vector2 v2 = {b.position.x - size, b.position.y + size};
  Vector2 v3 = {b.position.x + size, b.position.y + size};

  DrawTriangle(v1, v2, v3, BLACK);
}

void init_movement(int index) {
  float angle = static_cast<float>(rand()) / RAND_MAX * 2 * 3.1415926f;
  boids[index].angle = angle;

  float speed = 0.0;
  boids[index].velocity.x = cos(angle) * speed;
  boids[index].velocity.y = sin(angle) * speed;
}

void move_boid(int index) {
  boids[index].velocity.x += boids[index].steering.x;
  boids[index].velocity.y += boids[index].steering.y;

  normalise_velocity(index, MAX_SPEED);

  boids[index].position.x += boids[index].velocity.x;
  boids[index].position.y += boids[index].velocity.y;
}

Vector2 alignment(std::vector<boid> &vec, boid &b) {
  std::vector<boid> neighbours = find_neighbours(vec, b);
  Vector2 desired_velocity = average_velocity(neighbours);
  Vector2 steering = {0, 0};

  steering.x += desired_velocity.x - b.velocity.x;
  steering.y += desired_velocity.y - b.velocity.y;

  float magnitude = sqrt(steering.x * steering.x + steering.y * steering.y);

  if (magnitude > MAX_STEERING) {
    steering.x = steering.x * (MAX_STEERING / magnitude);
    steering.y = steering.y * (MAX_STEERING / magnitude);
  }
  return steering;
}

Vector2 cohesion(std::vector<boid> &vec, boid &b) {
  std::vector<boid> neighbours = find_neighbours(vec, b);

  Vector2 avg_pos = average_position(neighbours);
  Vector2 steering = {0, 0};

  steering.x += avg_pos.x - b.position.x;
  steering.y += avg_pos.y - b.position.y;

  float magnitude = sqrt(steering.x * steering.x + steering.y * steering.y);

  // normalisation
  if (magnitude > 0) {
    steering.x = steering.x * (MAX_STEERING / magnitude);
    steering.y = steering.y * (MAX_STEERING / magnitude);
  }

  return steering;
}

Vector2 separation(std::vector<boid> &vec, boid &b) {
  std::vector<boid> neighbours = find_neighbours(vec, b);

  Vector2 steering = {0, 0};
  int nearby_boids = 0;

  for (size_t i = 0; i < neighbours.size(); ++i) {
    float dx = b.position.x - neighbours[i].position.x;
    float dy = b.position.y - neighbours[i].position.y;
    float distance = std::sqrt(dx * dx + dy * dy);

    if (distance > 0.0f) {
      nearby_boids++;
      steering.x += dx / distance;
      steering.y += dy / distance;
    }
  }

  // Averaging the result
  if (nearby_boids > 0) {
    steering.x /= nearby_boids;
    steering.y /= nearby_boids;
  }

  // Normalize the steering force to prevent it from getting too large
  float magnitude =
      std::sqrt(steering.x * steering.x + steering.y * steering.y);
  if (magnitude > MAX_STEERING) {
    steering.x = steering.x * (MAX_STEERING / magnitude);
    steering.y = steering.y * (MAX_STEERING / magnitude);
  }
  return steering;
}

void wrap_boid(boid &b, float width, float height) {
  if (b.position.x > width)
    b.position.x = 0;
  if (b.position.x < 0)
    b.position.x = width;
  if (b.position.y > height)
    b.position.y = 0;
  if (b.position.y < 0)
    b.position.y = height;
}