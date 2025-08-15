#include "../include/main.h"
#include "raylib.h"
#include <vector>

Vector2 move_boid();

float size = 10;

void create_boid(Vector2 pos) {
  Vector2 v1 = {pos.x, pos.y - size};
  Vector2 v2 = {pos.x - size, pos.y + size};
  Vector2 v3 = {pos.x + size, pos.y + size};

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

Vector2 move_boid() {
  // TODO
}