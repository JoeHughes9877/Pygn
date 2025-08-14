#include "../include/main.h"
#include "../include/utils.h"
#include "raylib.h"

int main(void) {
  InitWindow(800, 450, "raylib [core] exampwle - basic window");

  struct boid b = {{10, 0}, {1, 25}, {19, 25}};

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    create_boid(b.v1, b.v2, b.v3);

    EndDrawing();
  }

  CloseWindow();
  return 0;
}