#include "../include/boid.h"
#include "../include/utils.h"
#include "raylib.h"
#include <cmath>
#include <cstdlib>
#include <vector>

float size = 10;
const float MAX_SPEED = 2.5;
const float MAX_STEERING = 2.5;

void init_movement(int index);

void create_boid(Vector2 pos) {
  boid b;
  b.position = pos;
  b.velocity = {0, 0};
  b.angle = 0;
  b.detection_area = 0.1f;
  b.steering.x = 0;
  b.steering.y = 0;
  boids.push_back(b);
  int arr_len = boids.size();

  init_movement(arr_len - 1);
}

void render_boid(Vector2 pos) {
  Vector2 v1 = {pos.x, pos.y - size};
  Vector2 v2 = {pos.x - size, pos.y + size};
  Vector2 v3 = {pos.x + size, pos.y + size};

  DrawTriangle(v1, v2, v3, BLACK);
}

void init_movement(int index) {
  float angle = static_cast<float>(rand()) / RAND_MAX * 2 * 3.1415926f;
  boids[index].angle = angle;

  float speed = 2.0;
  boids[index].velocity.x = cos(angle) * speed;
  boids[index].velocity.y = sin(angle) * speed;
}

void move_boid(int index) {
  boids[index].velocity.x += boids[index].steering.x;
  boids[index].velocity.y += boids[index].steering.y;

  vector_normalisation(index, MAX_SPEED);

  boids[index].position.x += boids[index].velocity.x;
  boids[index].position.y += boids[index].velocity.y;

  boids[index].steering.x = 0;
  boids[index].steering.y = 0;
}

void alignment(std::vector<boid> &vec, boid &b) {

  Vector2 desired_velocity = average(vec);

  b.steering.x = desired_velocity.x - b.velocity.x;
  b.steering.y = desired_velocity.y - b.velocity.y;

  float magnitude =
      sqrt(b.steering.x * b.steering.x + b.steering.y * b.steering.y);

  if (magnitude > MAX_STEERING) {
    b.steering.x = b.steering.x * (MAX_STEERING / magnitude);
    b.steering.y = b.steering.y * (MAX_STEERING / magnitude);
  }
}

void cohesion(std::vector<boid> &vec, boid &b) {

  Vector2 avg_pos = average(vec);

  b.steering.x = avg_pos.x - b.position.x;
  b.steering.y = avg_pos.y - b.position.y;
}

void separation(std::vector<boid> &vec, boid &b) {
  int amount_of_boids = vec.size();

  // converting 2D to 3D as CheckCollisionSpheres is 3D exclusive (y is 0.0f as
  // its still "2D")
  Vector3 boid_pos_3D = {b.position.x, 0.0f, b.position.y};

  for (int i = 0; i < amount_of_boids; i++) {
    Vector3 other_boid_pos_3D = {boids[i].position.x, 0.0f,
                                 boids[i].position.y};

    bool detected =
        CheckCollisionSpheres(boid_pos_3D, b.detection_area, other_boid_pos_3D,
                              boids[i].detection_area);

    if (&boids[i] != &b && detected) {
      float dx = b.position.x - vec[i].position.x;
      float dy = b.position.y - vec[i].position.y;

      float distance = std::sqrt(dx * dx + dy * dy);

      float strength = 1.0f - distance;

      b.steering.x += dx / distance * strength;
      b.steering.y += dy / distance * strength;
    };
  }
}

void wrap_boid(boid &b, float width, float height) {
  if (b.position.x > width)
    b.position.x = 0;
  if (b.position.x < 0)
    b.position.x = width;
  if (b.position.y > height)
    b.position.y = 0;
  if (b.position.y < 0)
    b.position.y = height;
}
