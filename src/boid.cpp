#include "../include/boid.h"
#include "../include/utils.h"
#include "raylib.h"
#include <cmath>
#include <cstdlib>
#include <vector>

float size = 10;
const float MAX_SPEED = 3.5f;
const float MAX_STEERING = 0.10f;

void init_movement(int index);

void create_boid(Vector2 pos) {
  boid b;
  b.position = pos;
  b.velocity = {0, 0};
  b.angle = 0;
  b.detection_area = 70.0f;
  b.steering = {0, 0};

  boids.push_back(b);
  int arr_len = boids.size();

  init_movement(arr_len - 1);
}

void render_boid(boid b) {
  Vector2 v1 = {b.position.x, b.position.y - size};
  Vector2 v2 = {b.position.x - size, b.position.y + size};
  Vector2 v3 = {b.position.x + size, b.position.y + size};

  DrawTriangle(v1, v2, v3, WHITE);
}

void init_movement(int index) {
  float angle = static_cast<float>(rand()) / RAND_MAX * 2 * 3.1415926f;
  boids[index].angle = angle;

  float speed =
      1.0f + static_cast<float>(rand()) / RAND_MAX * (MAX_SPEED * 0.5f);
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

// alignment with medium radius (~60)
Vector2 alignment(std::vector<boid> &vec, boid &b) {
  std::vector<boid> neighbours = find_neighbours(vec, b, 60.0f);
  if (neighbours.empty())
    return {0, 0};

  Vector2 desired_velocity = average_velocity(neighbours);

  float mag = sqrtf(desired_velocity.x * desired_velocity.x +
                    desired_velocity.y * desired_velocity.y);
  if (mag > 0) {
    desired_velocity.x = desired_velocity.x / mag * MAX_SPEED;
    desired_velocity.y = desired_velocity.y / mag * MAX_SPEED;
  }

  Vector2 steering = {desired_velocity.x - b.velocity.x,
                      desired_velocity.y - b.velocity.y};

  float magnitude = sqrtf(steering.x * steering.x + steering.y * steering.y);
  if (magnitude > MAX_STEERING) {
    steering.x *= (MAX_STEERING / magnitude);
    steering.y *= (MAX_STEERING / magnitude);
  }
  return steering;
}

Vector2 cohesion(std::vector<boid> &vec, boid &b) {
  std::vector<boid> neighbours = find_neighbours(vec, b, 80.0f);
  if (neighbours.empty())
    return {0, 0};

  Vector2 avg_pos = average_position(neighbours);
  Vector2 desired = {avg_pos.x - b.position.x, avg_pos.y - b.position.y};

  float mag = sqrtf(desired.x * desired.x + desired.y * desired.y);
  if (mag > 0) {
    desired.x = desired.x / mag * MAX_SPEED;
    desired.y = desired.y / mag * MAX_SPEED;
  }

  Vector2 steering = {desired.x - b.velocity.x, desired.y - b.velocity.y};

  float magnitude = sqrtf(steering.x * steering.x + steering.y * steering.y);
  if (magnitude > MAX_STEERING) {
    steering.x *= (MAX_STEERING / magnitude);
    steering.y *= (MAX_STEERING / magnitude);
  }
  return steering;
}

Vector2 separation(std::vector<boid> &vec, boid &b) {
  std::vector<boid> neighbours = find_neighbours(vec, b, 25.0f);
  if (neighbours.empty())
    return {0, 0};

  Vector2 steering = {0, 0};

  for (auto &n : neighbours) {
    float dx = b.position.x - n.position.x;
    float dy = b.position.y - n.position.y;
    float dist2 = dx * dx + dy * dy;

    if (dist2 > 0.0f) {
      steering.x += dx / dist2; // inverse-square push
      steering.y += dy / dist2;
    }
  }

  float mag = sqrtf(steering.x * steering.x + steering.y * steering.y);
  if (mag > 0) {
    steering.x = steering.x / mag * MAX_SPEED;
    steering.y = steering.y / mag * MAX_SPEED;
  }

  float magnitude = sqrtf(steering.x * steering.x + steering.y * steering.y);
  if (magnitude > MAX_STEERING) {
    steering.x *= (MAX_STEERING / magnitude);
    steering.y *= (MAX_STEERING / magnitude);
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
