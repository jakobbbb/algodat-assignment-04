#include "closest.hpp"
#include <cassert>
#include <cmath>
#include <iostream>
#include <ostream>
#include <random>
#include <set>
#include "mergesort.hpp"

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

/**
 * Get the closest pair that is split across the two halves.
 */
std::pair<point, point> combine(std::vector<point> const& y,
                                float l_x,
                                std::pair<point, point> const& pair_1,
                                std::pair<point, point> const& pair_2) {
  auto d1 = distance(pair_1);
  auto d2 = distance(pair_2);
  std::pair<point, point> pair_3;
  float d;
  if (d1 < d2) {
    pair_3 = pair_1;
    d = d1;
  } else {
    pair_3 = pair_2;
    d = d2;
  }
  std::vector<point> y_prime;
  for (auto const& p : y) {
    if (l_x - d <= p.x || p.x <= l_x + d) {
      y_prime.push_back(p);
    }
  }
  for (std::size_t i = 0; i < y_prime.size(); ++i) {
    std::size_t j = 1;
    while (j <= 7 && (i + j) < y_prime.size()) {
      auto d3 = distance(std::make_pair(y_prime[i], y_prime[i + j]));
      if (d3 < d) {
        pair_3 = std::make_pair(y_prime[i], y_prime[i + j]);
        d = d3;
      }
      ++j;
    }
  }
  return pair_3;
}

std::pair<point, point> closest(std::vector<point> const& x,
                                std::vector<point> const& y) {
  if (x.size() == 2)
    return std::make_pair(x[0], x[1]);
  if (x.size() == 3)
    return closest_naive(x);
  std::size_t m = x.size() / 2;
  float l_x = (x[m].x + x[m + 1].x) / 2.f;
  auto x_l = std::vector<point>(x.begin(), x.begin() + m);
  auto x_r = std::vector<point>(x.begin() + m, x.end());
  assert(x_l.size() + x_r.size() == x.size());
  auto pair_1 = closest(x_l, y);
  auto pair_2 = closest(x_r, y);
  auto pair_3 = combine(y, l_x, pair_1, pair_2);
  auto d1 = distance(pair_1);
  auto d2 = distance(pair_2);
  auto d3 = distance(pair_3);
  if (d1 <= d2 && d1 <= d3)
    return pair_1;
  else if (d2 <= d1 && d2 <= d3)
    return pair_2;
  else
    return pair_3;
}

std::pair<point, point> closest(std::vector<point> const& points) {
  if (points.size() < 2) {
    throw "Must have at least two points!";
  }
  return closest(mergesort_x(points), mergesort_y(points));
}
