#ifndef POINT_HPP
#define POINT_HPP
#include <vector>
#include <cmath>
#include <iostream>
#include <ostream>
#include <random>

/** 2D Point. */
struct point {
  float x;
  float y;
};

/** Test two points for equality. */
#define POINT_EQUALITY_EPSILON 0.001f
bool operator==(point const& lhs, point const& rhs);

/** Print a point. */
std::ostream& operator<<(std::ostream& os, point const& p);

/** Distance between two points. */
float distance(std::pair<point, point> const& points);

/**
 * Randomly generate a set of `n` points between `min` and `max`.
 */
std::vector<point> random_points(std::size_t n,
                                 point min = {0.f, 0.f},
                                 point max = {1.f, 1.f});

/**
 * Print a set of points separated by newlines to `os`.  Individual coordinates
 * are separated by spaces.
 */
std::ostream& print_points(std::ostream& os, std::vector<point> const& points);

#endif  // POINT_HPP