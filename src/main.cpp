#include "../include/main.h"
#include "../include/utils.h"
#include "raylib.h"

int main(void) {
  InitWindow(800, 450, "raylib [core] exampwle - basic window");

  SetTargetFPS(10);

  struct boid b = {{10, 0}, {1, 25}, {19, 25}};

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    create_boid(b.v1, b.v2, b.v3);

    b.v1.x += .5;
    b.v1.y += .5;

    b.v2.x += .5;
    b.v2.y += .5;

    b.v3.x += .5;
    b.v3.y += .5;

    EndDrawing();
  }

  CloseWindow();
  return 0;
}