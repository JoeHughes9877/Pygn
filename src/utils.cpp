#include "../include/boid.h"
#include <vector>

Vector2 average(std::vector<boid> &vec) {
  int arr_len = vec.size();
  Vector2 total_value = {0, 0};

  for (int i = 0; i < arr_len; i++) {
    total_value.x += vec[i].velocity.x;
    total_value.y += vec[i].velocity.y;
  }

  return {total_value.x / arr_len, total_value.y / arr_len};
}
