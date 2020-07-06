#include <iostream>
#include <ostream>
#include <random>
#include <set>
#include <cmath>

/** 2D Point. */
struct point {
  float x;
  float y;
};

/** Distance between two points. */
float distance(std::pair<point, point> const& points) {
  auto [lhs, rhs] = points;
  return std::sqrt(std::pow(rhs.x - lhs.x, 2) + std::pow(rhs.y - lhs.y, 2));
}

/**
 * Randomly generate a set of `n` points between `min` and `max`.
 * Note: `std::set` is an ordered container, and thus requires elements to have
 * a comparison operator.  Since no meaningful linear ordering exists for
 * two-dimensional points (analogous to complex numbers), an `std::vector` is
 * used here.
 */
std::vector<point> random_points(std::size_t n, point min, point max) {
  std::vector<point> points;
  for (std::size_t i = 0; i < n; ++i) {
    float r_1 = std::rand() / (float)RAND_MAX;
    float r_2 = std::rand() / (float)RAND_MAX;
    float x = min.x + r_1 * (max.x - min.x);
    float y = min.y + r_2 * (max.y - min.y);
    points.push_back({x, y});
  }
  return points;
}

/**
 * Print a set of points separated by newlines to `os`.  Individual coordinates
 * are separated by spaces.
 */
std::ostream& print_points(std::ostream& os, std::vector<point> const& points) {
  for (auto const& p : points)
    os << p.x << ' ' << p.y << '\n';
  return os;
}

/**
 * Naive O(n^2) algorithm for finding two closest points.
 * Used for verifying correctness of the efficient algorithm.
 */
std::pair<point, point> closest_naive(std::vector<point> points) {
  if (points.size() < 2) {
    throw "Must have at least two points!";
  }
  auto closest = std::make_pair(points[0], points[1]);
  for (auto const& p : points) {
    for (auto const& q : points) {
      auto pq = std::make_pair(p, q);
      if (distance(pq) > 0 && distance(pq) < distance(closest)) {
        closest = pq;
      }
    }
  }
  return closest;
}

int main() {
  auto points = random_points(30, {0.f, 0.f}, {1.f, 1.f});
  print_points(std::cout, points);
  auto closest = closest_naive(points);
  std::cout << "Closest points: "
    << closest.first.x << " " << closest.first.y << ", "
    << closest.second.x << " " << closest.second.y << "\n";
  return 0;
}
