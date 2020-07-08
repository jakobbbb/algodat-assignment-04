#include "point.hpp"

bool operator==(point const& lhs, point const& rhs) {
  auto eq_epsilon = [](float l, float r) -> bool {
    return std::abs(l - r) < POINT_EQUALITY_EPSILON;
  };
  return eq_epsilon(lhs.x, rhs.x) && eq_epsilon(lhs.y, rhs.y);
}

float distance(std::pair<point, point> const& points) {
  auto [lhs, rhs] = points;
  return std::sqrt(std::pow(rhs.x - lhs.x, 2) + std::pow(rhs.y - lhs.y, 2));
}

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

std::ostream& operator<<(std::ostream& os, point const& p) {
  os << "(" << p.x << ", " << p.y << ")";
  return os;
}

std::ostream& print_points(std::ostream& os, std::vector<point> const& points) {
  for (auto const& p : points)
    os << p.x << ' ' << p.y << '\n';
  return os;
}
