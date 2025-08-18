#include "../include/boid.h"
#include <cmath>
#include <vector>

Vector2 average_velocity(std::vector<boid> &vec) {
  int arr_len = vec.size();
  if (arr_len == 0) {
    return {0, 0};
  }
  Vector2 total_value = {0, 0};

  for (int i = 0; i < arr_len; i++) {
    total_value.x += vec[i].velocity.x;
    total_value.y += vec[i].velocity.y;
  }

  return {total_value.x / arr_len, total_value.y / arr_len};
}

Vector2 average_position(std::vector<boid> &vec) {
  int arr_len = vec.size();
  if (arr_len == 0) {
    return {0, 0};
  }
  Vector2 total_value = {0, 0};

  for (int i = 0; i < arr_len; i++) {
    total_value.x += vec[i].position.x;
    total_value.y += vec[i].position.y;
  }

  return {total_value.x / arr_len, total_value.y / arr_len};
}

void normalise_velocity(int index, const int MAX_SPEED) {
  float magnitude = sqrt(boids[index].velocity.x * boids[index].velocity.x +
                         boids[index].velocity.y * boids[index].velocity.y);

  if (magnitude > MAX_SPEED) {
    float scale = MAX_SPEED / magnitude;
    boids[index].velocity.x *= scale;
    boids[index].velocity.y *= scale;
  }
}

std::vector<boid> find_neighbours(std::vector<boid> &vec, boid b) {
  std::vector<boid> neighbours;
  int amount_of_boids = boids.size();

  for (int i = 0; i < amount_of_boids; i++) {
    float dx = b.position.x - vec[i].position.x;
    float dy = b.position.y - vec[i].position.y;
    float distance = std::sqrt(dx * dx + dy * dy);

    if (&vec[i] != &b && distance < b.detection_area && distance > 0.0f) {
      neighbours.push_back(vec[i]);
    }
  }
  return neighbours;
}