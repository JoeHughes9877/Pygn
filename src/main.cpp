#include "../include/main.h"
#include "../include/boid.h"
#include "raylib.h"
#include <bits/stdc++.h>
#include <vector>

std::vector<boid> boids;

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

int main(void) {
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Boids simulation");
  SetTargetFPS(120);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLUE);

    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
      Vector2 mouse_pos = GetMousePosition();
      create_boid(mouse_pos);
    }

    for (auto &boid : boids) {

      Vector2 alignment_force = alignment(boids, boid);
      Vector2 cohesion_force = cohesion(boids, boid);
      Vector2 separation_force = separation(boids, boid);

      // Apply forces with weights
      float separation_weight = 3.5f;
      float alignment_weight = 1.0f;
      float cohesion_weight = 1.0f;

      boid.steering.x += (separation_force.x * separation_weight) +
                         (alignment_force.x * alignment_weight) +
                         (cohesion_force.x * cohesion_weight);
      boid.steering.y += (separation_force.y * separation_weight) +
                         (alignment_force.y * alignment_weight) +
                         (cohesion_force.y * cohesion_weight);

      wrap_boid(boid, SCREEN_WIDTH, SCREEN_HEIGHT);
      render_boid(boid);
      move_boid(&boid);
    }

    EndDrawing();
  }
  CloseWindow();
  return 0;
}