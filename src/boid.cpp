#include "../include/boid.h"
#include "raylib.h"
#include <cmath>
#include <cstdlib>
#include <vector>

float size = 10;

void init_movement(int index);

void create_boid(Vector2 pos) {
  boid b;
  b.position = pos;
  b.velocity = {0, 0};
  b.angle = 0;

  boids.push_back(b);
  int arr_len = boids.size();

  init_movement(arr_len - 1);
}

void render_boid(Vector2 pos) {
  Vector2 v1 = {pos.x, pos.y - size};
  Vector2 v2 = {pos.x - size, pos.y + size};
  Vector2 v3 = {pos.x + size, pos.y + size};

  DrawTriangle(v1, v2, v3, BLACK);
}

void init_movement(int index) {
  float angle = static_cast<float>(rand()) / RAND_MAX * 2 * 3.1415926f;
  boids[index].angle = angle;

  float speed = 2.0f;
  boids[index].velocity.x = cos(angle) * speed;
  boids[index].velocity.y = sin(angle) * speed;
}

void move_boid(int index) {
  boids[index].position.x += boids[index].velocity.x;
  boids[index].position.y += boids[index].velocity.y;
}