#include "../include/boid.h"
#include <vector>

Vector2 average(std::vector<boid> &vec, bool use_velocity, bool use_position);
void normalise_velocity(boid *b, const int MAX_SPEED);
std::vector<boid> find_neighbours(std::vector<boid> &vec, const boid &b,
                                  float detect);
Vector2 limit_steering(Vector2 steering, const float MAX_STEERING);