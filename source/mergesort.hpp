#include <algorithm>

template <typename Container, typename Comparision>
Container mergesort(Container const& c, Comparision less) {
  // TODO
  auto r{c};
  std::sort(std::begin(r), std::end(r), less);
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
