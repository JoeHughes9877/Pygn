#include <vector>

#include "raylib.h"

struct boid {
  Vector2 position;
  Vector2 velocity;
  float angle;
};

extern std::vector<boid> boids;