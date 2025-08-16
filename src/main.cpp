#include "../include/main.h"
#include "../include/boid.h"
#include "raylib.h"
#include <bits/stdc++.h>
#include <vector>

std::vector<boid> boids;

int main(void) {
  InitWindow(800, 450, "Boids simulation");
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
      render_boid(boids[i].position);
      move_boid(i);
      detect_other_boids(boids[i]);
      wrap_boid(boids[i], 800, 450);
    }

    EndDrawing();
  }
  CloseWindow();
  return 0;
}