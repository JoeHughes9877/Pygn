#include "../include/utils.h"
#include "raylib.h"

int main(void) {
  InitWindow(800, 450, "raylib [core] exampwle - basic window");

  Texture2D sprite = LoadTexture("boid.jpg");

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    create_boid(sprite, 0, 0);

    EndDrawing();
  }

  UnloadTexture(sprite);
  CloseWindow();
  return 0;
}