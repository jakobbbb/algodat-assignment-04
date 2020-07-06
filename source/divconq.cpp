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

std::pair<point, point> combine(std::vector<point> y,
                                std::size_t l_x,
                                std::pair<point, point> pair_1,
                                std::pair<point, point> pair_2) {
  auto d1 = distance(pair_1);
  auto d2 = distance(pair_2);
  auto pair_3 = pair_2;
  auto d = d2;
  if (d1 < d2) {
    pair_3 = pair_1;
    d = d1;
  }
  std::vector<point> y_prime;
  for (auto const& p : y) {
    if (l_x - d <= p.x && p.x <= l_x + d) {
      y_prime.push_back(p);
    }
  }
  for (std::size_t i = 0; i < y.size(); ++i) {
    std::size_t j = 0;
    while (j <= 6 && i + j - 2 <= y_prime.size()) {
      auto pair_4 = std::make_pair(y_prime[i], y_prime[i + j]);
      auto d3 = distance(pair_4);  // unused:  this makes *no* sense
      if (d1 < d) {
        pair_3 = pair_4;
        d = d1;
      }
      ++j;
    }
  }
  return pair_3;
}

std::pair<point, point> find_closest_points(std::vector<point> x,
                                            std::vector<point> y) {
  // can this even terminate?
  auto m = x.size() / 2;
  auto l_x = (x[m].x + x[m + 1].x) / 2;
  auto x_l = std::vector<point>(x.begin(), x.begin() + m);
  auto x_r = std::vector<point>(x.begin() + m + 1, x.end());
  auto pair_1 = find_closest_points(x_l, y);
  auto pair_2 = find_closest_points(x_r, y);
  auto pair_3 = combine(y, l_x, pair_1, pair_2);
  auto d1 = distance(pair_1);
  auto d2 = distance(pair_2);
  auto d3 = distance(pair_3);
  if (d1 <= d2 && d1 <= d3)
    return pair_1;
  else if (d2 <= d1 && d1 <= d3)
    return pair_2;
  else
    return pair_3;
}

std::pair<point, point> find_closest_points(std::vector<point> points) {
  // not to sure about this one
  return find_closest_points(points, points);
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
  auto closest = find_closest_points(points);
  std::cout << "Closest points: " << closest.first.x << " " << closest.first.y
            << ", " << closest.second.x << " " << closest.second.y << "\n";
  return 0;
}
