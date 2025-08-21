#include "../include/boid.h"
#include "../include/utils.h"
#include "raylib.h"
#include <cmath>
#include <cstdlib>
#include <vector>

const float MAX_SPEED = 3.5f;
const float MAX_STEERING = 0.10f;
const float DETECTION_AREA = 70.0f;

void init_movement(int index);

void create_boid(Vector2 pos) {
  boid b;
  b.position = pos;
  b.velocity = {0, 0};
  b.angle = 0;
  b.detection_area = DETECTION_AREA;
  b.steering = {0, 0};

  boids.push_back(b);
  int arr_len = boids.size();

  init_movement(arr_len - 1);
}

void render_boid(boid b) {
  double angle = atan2(b.velocity.y, b.velocity.x);
  float size = 10;

  Vector2 pos1 = {size, 0};
  Vector2 pos2 = {-size, -size / 2};
  Vector2 pos3 = {-size, size / 2};

  Vector2 v1 = {static_cast<float>(b.position.x + pos1.x * cos(angle) -
                                   pos1.y * sin(angle)),
                static_cast<float>(b.position.y + pos1.x * sin(angle) +
                                   pos1.y * cos(angle))};

  Vector2 v2 = {static_cast<float>(b.position.x + pos2.x * cos(angle) -
                                   pos2.y * sin(angle)),
                static_cast<float>(b.position.y + pos2.x * sin(angle) +
                                   pos2.y * cos(angle))};

  Vector2 v3 = {static_cast<float>(b.position.x + pos3.x * cos(angle) -
                                   pos3.y * sin(angle)),
                static_cast<float>(b.position.y + pos3.x * sin(angle) +
                                   pos3.y * cos(angle))};

  DrawTriangle(v1, v2, v3, WHITE);
}

void init_movement(int index) {
  float angle = static_cast<float>(rand()) / RAND_MAX * 2 * PI;
  boids[index].angle = angle;

  float speed =
      1.0f + static_cast<float>(rand()) / RAND_MAX * (MAX_SPEED * 0.5f);
  boids[index].velocity.x = cos(angle) * speed;
  boids[index].velocity.y = sin(angle) * speed;
}

void move_boid(boid *b) {

  b->velocity.x += b->steering.x;
  b->velocity.y += b->steering.y;

  normalise_velocity(b, MAX_SPEED);

  b->position.x += b->velocity.x;
  b->position.y += b->velocity.y;
}

Vector2 alignment(std::vector<boid> &vec, boid &b) {
  std::vector<boid> neighbours = find_neighbours(vec, b, 60.0f);
  if (neighbours.empty())
    return {0, 0};

  Vector2 desired_velocity = average(neighbours, true, false);

  float mag = sqrtf(desired_velocity.x * desired_velocity.x +
                    desired_velocity.y * desired_velocity.y);
  if (mag > 0) {
    desired_velocity.x = desired_velocity.x / mag * MAX_SPEED;
    desired_velocity.y = desired_velocity.y / mag * MAX_SPEED;
  }

  Vector2 steering = {desired_velocity.x - b.velocity.x,
                      desired_velocity.y - b.velocity.y};

  steering = limitSteering(steering, MAX_STEERING);

  return steering;
}

Vector2 cohesion(std::vector<boid> &vec, boid &b) {
  std::vector<boid> neighbours = find_neighbours(vec, b, 80.0f);
  if (neighbours.empty())
    return {0, 0};

  Vector2 avg_pos = average(neighbours, false, true);
  Vector2 desired = {avg_pos.x - b.position.x, avg_pos.y - b.position.y};

  float mag = sqrtf(desired.x * desired.x + desired.y * desired.y);
  if (mag > 0) {
    desired.x = desired.x / mag * MAX_SPEED;
    desired.y = desired.y / mag * MAX_SPEED;
  }

  Vector2 steering = {desired.x - b.velocity.x, desired.y - b.velocity.y};

  steering = limitSteering(steering, MAX_STEERING);
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

  steering = limitSteering(steering, MAX_STEERING);
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
