#include "../include/main.h"
#include "../include/utils.h"
#include "raylib.h"
#include <bits/stdc++.h>
#include <vector>

std::vector<boid> boids;

int main(void) {
  InitWindow(800, 450, "Boids simulation");
  SetTargetFPS(10);

  boids = {
      {{0, 10}, {1, 25}, {19, 25}},
      {{10, 50}, {1, 100}, {50, 25}},
  };

  while (!WindowShouldClose()) {
    int amount_of_boids = 0;

    BeginDrawing();
    ClearBackground(WHITE);

    amount_of_boids = boids.size();

    for (int i = 0; i < amount_of_boids; i++) {
      render_boid(boids[i].v1, boids[i].v2, boids[i].v3);

      boids[i].v1.x += 1;
      boids[i].v1.y += 1;

      boids[i].v2.x += 1;
      boids[i].v2.y += 1;

      boids[i].v3.x += 1;
      boids[i].v3.y += 1;
    }
    EndDrawing();
  }

  CloseWindow();
  return 0;
}