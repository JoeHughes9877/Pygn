#include "../include/boid.h"
#include <vector>

Vector2 average_velocity(std::vector<boid> &vec);
Vector2 average_position(std::vector<boid> &vec);
void vector_normalisation(int index, const int MAX_SPEED);
std::vector<boid> find_neighbours(std::vector<boid> &vec, boid b);