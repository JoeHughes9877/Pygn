#include "../include/boid.h"
#include <cmath>
#include <stdexcept>
#include <vector>

Vector2 average(std::vector<boid> &vec, bool use_velocity, bool use_position) {
  int arr_len = vec.size();
  if (arr_len == 0) {
    return {0, 0};
  }
  Vector2 total_value = {0, 0};

  for (auto b : vec) {
    if (use_velocity) {
      total_value.x += b.velocity.x;
      total_value.y += b.velocity.y;
    } else if (use_position) {
      total_value.x += b.position.x;
      total_value.y += b.position.y;
    } else {
      throw std::logic_error(
          "Either use_velocity or use_position must be true.");
    }
  }

  return {total_value.x / arr_len, total_value.y / arr_len};
}

void normalise_velocity(boid *b, const int MAX_SPEED) {
  float magnitude =
      sqrt(b->velocity.x * b->velocity.x + b->velocity.y * b->velocity.y);

  if (magnitude > MAX_SPEED) {
    float scale = MAX_SPEED / magnitude;
    b->velocity.x *= scale;
    b->velocity.y *= scale;
  }
}

std::vector<boid> find_neighbours(std::vector<boid> &vec, boid &b,
                                  float detect) {
  std::vector<boid> neighbours;
  for (auto &other : vec) {
    if (&other == &b)
      continue;

    float dx = other.position.x - b.position.x;
    float dy = other.position.y - b.position.y;
    float distance = std::sqrt(dx * dx + dy * dy);

    if (distance < detect && distance > 0.0f) {
      neighbours.push_back(other);
    }
  }

  return neighbours;
}

Vector2 limitSteering(Vector2 steering, const float MAX_STEERING) {
  float magnitude = sqrtf(steering.x * steering.x + steering.y * steering.y);
  if (magnitude > MAX_STEERING) {
    steering.x *= (MAX_STEERING / magnitude);
    steering.y *= (MAX_STEERING / magnitude);
  }
  return steering;
}
