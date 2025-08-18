#include "../include/main.h"
#include "../include/boid.h"
#include "raylib.h"
#include <bits/stdc++.h>
#include <vector>

std::vector<boid> boids;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 450;

int main(void) {
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Boids simulation");
  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) ||
        IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
      Vector2 mouse_pos = GetMousePosition();

      create_boid(mouse_pos);
    }

    int amount_of_boids = boids.size();
    for (int i = 0; i < amount_of_boids; i++) {

      Vector2 alignment_force = alignment(boids, boids[i]);
      Vector2 cohesion_force = cohesion(boids, boids[i]);
      Vector2 separation_force = separation(boids, boids[i]);

      // Apply forces with weights
      float separation_weight = 2.8f;
      float alignment_weight = 1.0f;
      float cohesion_weight = 0.8f;

      boids[i].steering.x += (separation_force.x * separation_weight) +
                             (alignment_force.x * alignment_weight) +
                             (cohesion_force.x * cohesion_weight);
      boids[i].steering.y += (separation_force.y * separation_weight) +
                             (alignment_force.y * alignment_weight) +
                             (cohesion_force.y * cohesion_weight);

      wrap_boid(boids[i], SCREEN_WIDTH, SCREEN_HEIGHT);
      render_boid(boids[i]);
      move_boid(i);
    }

    EndDrawing();
  }
  CloseWindow();
  return 0;
}