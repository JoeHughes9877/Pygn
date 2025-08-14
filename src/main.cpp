#include "../include/main.h"
#include "../include/utils.h"
#include "raylib.h"
#include <bits/stdc++.h>
#include <vector>

std::vector<boid> boids = {{10, 0}, {1, 25}, {19, 25}};

int main(void) {
  InitWindow(800, 450, "raylib [core] exampwle - basic window");
  SetTargetFPS(10);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    int amount_of_boids = boids.size();

    for (int i = 0; i < amount_of_boids; i++) {
      boids[i].v1.x += 5;
      boids[i].v1.y += 5;

      boids[i].v2.x += 5;
      boids[i].v2.y += 5;

      boids[i].v3.x += 5;
      boids[i].v3.y += 5;
    }

    EndDrawing();
  }

  CloseWindow();
  return 0;
}