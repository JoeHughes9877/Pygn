#include "../include/main.h"
#include "raylib.h"

void create_boid(Vector2 v1, Vector2 v2, Vector2 v3) {
  DrawTriangle(v1, v2, v3, BLACK);

  boids.push_back({v1, v2, v3});
}