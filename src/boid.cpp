#include "../include/boid.h"
#include "raylib.h"
#include <cmath>
#include <vector>

float size = 10;

void create_boid(Vector2 pos) {
  boid b;
  b.position = pos;
  b.velocity = {5, 5};
  b.angle = 0; // for now

  boids.push_back(b);
}

void render_boid(Vector2 pos) {
  Vector2 v1 = {pos.x, pos.y - size};
  Vector2 v2 = {pos.x - size, pos.y + size};
  Vector2 v3 = {pos.x + size, pos.y + size};

  DrawTriangle(v1, v2, v3, BLACK);
}

void move_boid(boid b, int index) {
  boids[index].angle = atan2(b.velocity.y, b.velocity.x);

  boids[index].position.x += boids[index].velocity.x;
  boids[index].position.y += boids[index].velocity.y;
}