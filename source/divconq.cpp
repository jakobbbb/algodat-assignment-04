#include <iostream>
#include <ostream>
#include <random>
#include <set>
#include <cmath>

struct point {
  float x;
  float y;
};

float distance(std::pair<point, point> const& points) {
  auto [lhs, rhs] = points;
  return std::sqrt(std::pow(rhs.x - lhs.x, 2) + std::pow(rhs.y - lhs.y, 2));
}

/**
 * Note:  Since `std::set` is ordered but there is no meaningful way of ordering
 * (i. e. comparing) points, a `std::vector` is used here.
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

std::ostream& print_points(std::ostream& os, std::vector<point> const& points) {
  for (auto const& p : points)
    os << p.x << ' ' << p.y << '\n';
  return os;
}

std::pair<point, point> naive(std::vector<point> points) {
  if (points.size() < 2)
    throw "Must have at least two points!";
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
  auto closest = naive(points);
  std::cout << "Closest points: "
    << closest.first.x << " " << closest.first.y << ", "
    << closest.second.x << " " << closest.second.y << "\n";
  return 0;
}
