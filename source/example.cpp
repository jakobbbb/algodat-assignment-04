#include <iostream>
#include "closest.hpp"

int main() {
  auto points = random_points(30, {0.f, 0.f}, {1.f, 1.f});
  print_points(std::cout, points);

  auto n = closest_naive(points);
  std::cout << "Closest points (naive):\t" << n.first << " " << n.second
            << " (d=" << distance(n) << ")\n";

  auto c = closest(points);
  std::cout << "Closest points (di&co):\t" << c.first << " " << c.second
            << " (d=" << distance(c) << ")\n";
  return 0;
}
