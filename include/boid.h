#ifndef BOID_H
#define BOID_H

#include "../include/main.h"
#include "raylib.h"

struct boid {
  Vector2 position;
  Vector2 velocity;
  float angle;
  float detection_area;
  float steering_x;
  float steering_y;
};

extern std::vector<boid> boids;

void create_boid(Vector2 pos);
void move_boid(int index);
void render_boid(Vector2 pos);
void detect_other_boids(boid &b);

void alignment(std::vector<boid> &vec, boid &b);
void cohesion(std::vector<boid> &vec, boid &b);
void separation(std::vector<boid> &vec, boid &b);
void wrap_boid(boid &b, float width, float height);

#endif