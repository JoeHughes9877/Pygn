#include "../include/boid.h"
#include "raylib.h"
#include <cmath>
#include <cstdlib>
#include <vector>

float size = 10;

void init_movement(int index);

void create_boid(Vector2 pos) {
  boid b;
  b.position = pos;
  b.velocity = {0, 0};
  b.angle = 0;
  b.detection_area = 100.0;
  b.steering_x = 0;
  b.steering_y = 0;

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

  float speed = 2.0f;
  boids[index].velocity.x = cos(angle) * speed;
  boids[index].velocity.y = sin(angle) * speed;
}

void move_boid(int index) {
  boids[index].velocity.x += boids[index].steering_x;
  boids[index].velocity.y += boids[index].steering_y;

  boids[index].position.x += boids[index].velocity.x;
  boids[index].position.y += boids[index].velocity.y;

  boids[index].steering_x = 0;
  boids[index].steering_y = 0;
}

void detect_other_boids(boid &b) {
  std::vector<boid> neighbours;

  int amount_of_boids = boids.size();

  // converting 2D to 3D as CheckCollisionSpheres is 3D exclusive (y is 0.0f as
  // its still "2D")
  Vector3 boid_pos_3D = {b.position.x, 0.0f, b.position.y};

  for (int i = 0; i < amount_of_boids; i++) {
    Vector3 other_boid_pos_3D = {boids[i].position.x, 0.0f,
                                 boids[i].position.y};

    bool detected =
        CheckCollisionSpheres(boid_pos_3D, 5.0f, other_boid_pos_3D, 0.5f);

    if (&boids[i] != &b && detected) {
      neighbours.push_back(boids[i]);
    }
  }
  if (neighbours.size() != 0) {
    alignment(neighbours, b);
    // cohesion(neighbours, b);
    // separation(neighbours, b);
  }
}

void alignment(std::vector<boid> &vec, boid &b) {
  int arr_len = vec.size();
  float total_value_x = 0;
  float total_value_y = 0;

  for (int i = 0; i < arr_len; i++) {
    total_value_x += vec[i].velocity.x;
    total_value_y += vec[i].velocity.y;
  }

  float desired_velocity_x = total_value_x / arr_len;
  float desired_velocity_y = total_value_y / arr_len;

  b.steering_x = desired_velocity_x - b.velocity.x;
  b.steering_y = desired_velocity_y - b.velocity.y;
}

void cohesion(std::vector<boid> &vec, boid b) { return; }

void separation(std::vector<boid> &vec, boid b) { return; }