#include "../include/boid.h"
#include <cmath>
#include <vector>

Vector2 average(std::vector<boid> &vec) {
  int arr_len = vec.size();
  Vector2 total_value = {0, 0};

  for (int i = 0; i < arr_len; i++) {
    total_value.x += vec[i].position.x;
    total_value.y += vec[i].position.y;
  }

  return {total_value.x / arr_len, total_value.y / arr_len};
}

void vector_normalisation(int index, const int MAX_SPEED) {
  float magnitude = sqrt(boids[index].velocity.x * boids[index].velocity.x +
                         boids[index].velocity.y * boids[index].velocity.y);

  if (magnitude > MAX_SPEED) {
    float scale = MAX_SPEED / magnitude;
    boids[index].velocity.x *= scale;
    boids[index].velocity.y *= scale;
  }
}
