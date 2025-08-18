#include "../include/boid.h"
#include "../include/utils.h"
#include "raylib.h"
#include <cmath>
#include <cstdlib>
#include <vector>

float size = 10;
const float MAX_SPEED = 2.5;
const float MAX_STEERING = 2.5;

void init_movement(int index);

void create_boid(Vector2 pos) {
  boid b;
  b.position = pos;
  b.velocity = {0, 0};
  b.angle = 0;
  b.detection_area = 25.0f;
  b.steering.x = 0;
  b.steering.y = 0;
  boids.push_back(b);
  int arr_len = boids.size();

  init_movement(arr_len - 1);
}

void render_boid(Vector2 pos) {
  Vector2 v1 = {pos.x, pos.y - size};
  Vector2 v2 = {pos.x - size, pos.y + size};
  Vector2 v3 = {pos.x + size, pos.y + size};

  DrawTriangle(v1, v2, v3, BLACK);
}

void init_movement(int index) {
  float angle = static_cast<float>(rand()) / RAND_MAX * 2 * 3.1415926f;
  boids[index].angle = angle;

  float speed = 2.0;
  boids[index].velocity.x = cos(angle) * speed;
  boids[index].velocity.y = sin(angle) * speed;
}

void move_boid(int index) {
  boids[index].velocity.x += boids[index].steering.x;
  boids[index].velocity.y += boids[index].steering.y;

  vector_normalisation(index, MAX_SPEED);

  boids[index].position.x += boids[index].velocity.x;
  boids[index].position.y += boids[index].velocity.y;

  boids[index].steering.x = 0;
  boids[index].steering.y = 0;
}

Vector2 alignment(std::vector<boid> &vec, boid &b) {
  Vector2 desired_velocity = average(vec);
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
  Vector2 avg_pos = average(vec);
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
  int amount_of_boids = boids.size();
  Vector2 steering = {0, 0};
  int nearby_boids = 0;

  for (int i = 0; i < amount_of_boids; i++) {
    float dx = b.position.x - vec[i].position.x;
    float dy = b.position.y - vec[i].position.y;
    float distance = std::sqrt(dx * dx + dy * dy);

    if (&boids[i] != &b && distance < b.detection_area && distance > 0.0f) {
      nearby_boids++;

      steering.x += dx / distance;
      steering.y += dy / distance;
    }
  }
  // averageing result
  if (nearby_boids > 0) {
    steering.x /= nearby_boids;
    steering.y /= nearby_boids;
  }

  float magnitude = sqrt(steering.x * steering.x + steering.y * steering.y);

  if (magnitude > MAX_STEERING) {
    steering.x = steering.x * (MAX_STEERING / magnitude);
    steering.y = steering.y * (MAX_STEERING / magnitude);
  }
  return steering;
}