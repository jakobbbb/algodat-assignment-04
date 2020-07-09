#include "closest.hpp"
#include <cassert>
#include <cmath>
#include <iostream>
#include <ostream>
#include <random>
#include <set>
#include "mergesort.hpp"

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
  auto pair_1 = closest(x_l, y);                  // Closest pair might be
  auto pair_2 = closest(x_r, y);                  // in one of the halves...
  auto pair_3 = combine(y, l_x, pair_1, pair_2);  // ...or split across them.
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
