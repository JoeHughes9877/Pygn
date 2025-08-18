#ifndef BOID_H
#define BOID_H

#include "../include/main.h"
#include "raylib.h"

struct boid {
  Vector2 position;
  Vector2 velocity;
  Vector2 steering;
  float angle;
  float detection_area;
};

extern std::vector<boid> boids;

void create_boid(Vector2 pos);
void move_boid(int index);
void render_boid(boid b);

Vector2 alignment(std::vector<boid> &vec, boid &b);
Vector2 cohesion(std::vector<boid> &vec, boid &b);
Vector2 separation(std::vector<boid> &vec, boid &b);
void wrap_boid(boid &b, float width, float height);

#endif