#ifndef MERGESORT_HPP
#define MERGESORT_HPP
#include <algorithm>
#include <vector>
#include "point.hpp"

template <typename Comparision>
/**
 * Sort a vector of points using merge sort.
 * For two points `p` and `q`, `less_eq(p, q)` is a function that returns true
 * iff `p` is considered less than or equal to `q`.  This is needed because
 * points may need to be sorted by their x or y coordinate.
 */
std::vector<point> mergesort(std::vector<point> const& c, Comparision less_eq) {
  if (c.size() <= 1) {
    return c;
  } else {
    std::size_t m = c.size() / 2;
    auto c_l = std::vector<point>(c.cbegin(), c.cbegin() + m);
    auto c_r = std::vector<point>(c.cbegin() + m, c.cend());
    c_l = mergesort(c_l, less_eq);
    c_r = mergesort(c_r, less_eq);
    return merge(c_l, c_r, less_eq);
  }
}

template <typename Comparision>
/**
 * Merge two sorted vectors of points.
 */
std::vector<point> merge(std::vector<point> const& c_l,
                         std::vector<point> const& c_r,
                         Comparision less_eq) {
  std::size_t size = c_l.size() + c_r.size();
  auto c = std::vector<point>(size);
  std::size_t i_l = 0;
  std::size_t i_r = 0;
  std::size_t i = 0;
  while (i_l < c_l.size() || i_r < c_r.size()) {
    if (i_l >= c_l.size()) {
      c[i] = c_r[i_r++];
    } else if (i_r >= c_r.size()) {
      c[i] = c_l[i_l++];
    } else if (less_eq(c_l[i_l], c_r[i_r])) {
      c[i] = c_l[i_l++];
    } else {
      c[i] = c_r[i_r++];
    }
    ++i;
  }
  return c;
}

/**
 * Sort a vector of points by x coordinate, from lowest to highest.
 */
std::vector<point> mergesort_x(std::vector<point> const& c);

/**
 * Sort a vector of points by y coordinate, from lowest to highest.
 */
std::vector<point> mergesort_y(std::vector<point> const& c);

#endif  // MERGESORT_HPP
