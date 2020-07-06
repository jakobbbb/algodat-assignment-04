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

/** Used for sorting with mergesort. */
bool operator<(point const& lhs, point const& rhs);

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

/**
 * Find the two points that are closest together.
 */
std::pair<point, point> closest(std::vector<point> points);

/**
 * Utility function for closest point algorithm.
 */
std::pair<point, point> closest(std::vector<point> x, std::vector<point> y);

/**
 * Utility function for closest point algorithm.
 */
std::pair<point, point> combine(std::vector<point> y,
                                std::size_t l_x,
                                std::pair<point, point> pair_1,
                                std::pair<point, point> pair_2);

/**
 * Naive O(n^2) algorithm for finding two closest points.
 * Used for verifying correctness of the efficient algorithm.
 */
std::pair<point, point> closest_naive(std::vector<point> points);
