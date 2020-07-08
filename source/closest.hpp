#ifndef CLOSEST_HPP
#define CLOSEST_HPP
#include <vector>
#include <cmath>
#include <iostream>
#include <ostream>
#include <random>
#include "point.hpp"

/**
 * Find the two points that are closest together.
 */
std::pair<point, point> closest(std::vector<point> const& points);

/**
 * Utility function for closest point algorithm.
 */
std::pair<point, point> closest(std::vector<point> const& x,
                                std::vector<point> const& y);

/**
 * Utility function for closest point algorithm.
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
