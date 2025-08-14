#include <vector>

#include "raylib.h"

struct boid {
  Vector2 v1;
  Vector2 v2;
  Vector2 v3;
};

extern std::vector<boid> boids;