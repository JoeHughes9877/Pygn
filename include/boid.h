#include "../include/main.h"
#include "raylib.h"

struct boid {
  Vector2 position;
  Vector2 velocity;
  float angle;
  float detection_area;
};

extern std::vector<boid> boids;

void create_boid(Vector2 pos);
void move_boid(int index);
void render_boid(Vector2 pos);
void detect_other_boids(boid b);
