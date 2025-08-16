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
void render_boid(Vector2 pos);

void alignment(std::vector<boid> &vec, boid &b);
void cohesion(std::vector<boid> &vec, boid &b);
void separation(std::vector<boid> &vec, boid &b);

#endif