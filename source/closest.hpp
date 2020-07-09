#ifndef CLOSEST_HPP
#define CLOSEST_HPP
#include <cmath>
#include <iostream>
#include <ostream>
#include <random>
#include <vector>
#include "point.hpp"

/**
 * Find the two points within a vector of points that are closest together.
 */
std::pair<point, point> closest(std::vector<point> const& points);

/**
 * Closest point algorithm, expecting the same vector of points as parameters,
 * sorted by x coordinate and y coordinate respectively,
 */
std::pair<point, point> closest(std::vector<point> const& x,
                                std::vector<point> const& y);

/**
 * Get the closest pair that is split across the two halves.
 */
std::pair<point, point> combine(std::vector<point> const& y,
                                std::size_t l_x,
                                std::pair<point, point> const& pair_1,
                                std::pair<point, point> const& pair_2);

/**
 * Naive O(n^2) algorithm for finding two closest points.
 * Used for verifying correctness of the efficient algorithm.
 */
std::pair<point, point> closest_naive(std::vector<point> points);
#endif  // CLOSEST_HPP
