#include <algorithm>
#include <vector>
#include "closest.hpp"

template <typename Comparision>
std::vector<point> mergesort(std::vector<point> const& c, Comparision less) {
  // TODO
  auto r{c};
  std::sort(std::begin(r), std::end(r), less);
  return r;
}

std::vector<point> mergesort_x(std::vector<point> const& c) {
  return mergesort(c, [](auto const& lhs, auto const& rhs){
      return lhs.x < rhs.x;
      });
}

std::vector<point> mergesort_y(std::vector<point> const& c) {
  return mergesort(c, [](auto const& lhs, auto const& rhs){
      return lhs.y < rhs.y;
      });
}
