#include "mergesort.hpp"

std::vector<point> mergesort_x(std::vector<point> const& c) {
  return mergesort(
      c, [](auto const& lhs, auto const& rhs) { return lhs.x <= rhs.x; });
}

std::vector<point> mergesort_y(std::vector<point> const& c) {
  return mergesort(
      c, [](auto const& lhs, auto const& rhs) { return lhs.y <= rhs.y; });
}
