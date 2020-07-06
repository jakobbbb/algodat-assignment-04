#include <algorithm>

template <typename Container>
Container mergesort(Container const& c) {
  // TODO
  auto r{c};
  std::sort(std::rbegin(r), std::rend(r));
  return r;
}
