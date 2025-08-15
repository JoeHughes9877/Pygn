#include "../include/boid.h"
#include "raylib.h"
#include <cstdlib>
#include <vector>

float size = 10;

void create_boid(Vector2 pos) {
  boid b;
  b.position = pos;
  b.velocity = {0, 0};
  b.angle = 0; // for now

  boids.push_back(b);
}

void render_boid(Vector2 pos) {
  Vector2 v1 = {pos.x, pos.y - size};
  Vector2 v2 = {pos.x - size, pos.y + size};
  Vector2 v3 = {pos.x + size, pos.y + size};

  DrawTriangle(v1, v2, v3, BLACK);
}

void move_boid(boid b) {
  // TODO
}