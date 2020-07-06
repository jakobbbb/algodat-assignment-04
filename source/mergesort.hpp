#include <algorithm>

template <typename Container, typename Comparision>
Container mergesort(Container const& c, Comparision less) {
  // TODO
  auto r{c};
  std::sort(std::rbegin(r), std::rend(r), less);
  return r;
}

template <typename Container>
Container mergesort_x(Container const& c) {
  return mergesort(c, [](auto const& lhs, auto const& rhs){
      return lhs.x < rhs.x;
      });
}

template <typename Container>
Container mergesort_y(Container const& c) {
  return mergesort(c, [](auto const& lhs, auto const& rhs){
      return lhs.y < rhs.y;
      });
}
