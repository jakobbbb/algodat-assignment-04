#ifndef MERGESORT_HPP
#define MERGESORT_HPP
#include <algorithm>
#include <vector>
#include "point.hpp"

template <typename Comparision>
std::vector<point> mergesort(std::vector<point> const& c, Comparision less_eq) {
  if (c.size() <= 1) {
    return c;
  } else {
    std::size_t m = c.size() / 2;
    auto c_l = std::vector<point>(c.cbegin(), c.cbegin() + m);
    auto c_r = std::vector<point>(c.cbegin() + m, c.cend());
    c_l = mergesort(c_l, less_eq);
    c_r = mergesort(c_r, less_eq);
  }
}
template <typename Comparision>
std::vector<point> merge(std::vector<point> const& c_l,
                         std::vector<point> const& c_r,
                         Comparision less_eq) {
  std::size_t size = c_l.size() + c_r.size();
  auto c = std::vector<point>(size);
  std::size_t firstPos = 0;
  std::size_t secondPos = 0;
  std::size_t targetPos = 0;
  while (firstPos < c_l.size() || secondPos < c_r.size()) {
    if (firstPos >= c_l.size()) {
      c[targetPos] = c_r[secondPos];
      secondPos++;
    } else if (secondPos >= c_r.size()) {
      c[targetPos] = c_l[firstPos];
      firstPos++;
    } else if (less_eq(c_l[firstPos], c_r[secondPos])) {
      c[targetPos] = c_l[firstPos];
      firstPos++;
    } else {
      c[targetPos] = c_r[secondPos];
      secondPos++;
    }
    targetPos++;
  }

  return c;
}

std::vector<point> mergesort_x(std::vector<point> const& c);

std::vector<point> mergesort_y(std::vector<point> const& c);

#endif  // MERGESORT_HPP
