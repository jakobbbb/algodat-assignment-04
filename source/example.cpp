#include <iostream>
#include "closest.hpp"

int main() {
  auto points = random_points(30, {0.f, 0.f}, {1.f, 1.f});
  std::cout << "# gnuplot script\nunset key\nset term png\n"
            << "set output 'plot.png'\n"
            << "plot '-', '-' w l\n";
  print_points(std::cout, points);
  std::cout << "e\n";

  auto n = closest_naive(points);
  auto c = closest(points);

  std::cout << c.first.x << " " << c.first.y << "\n"
            << c.second.x << " " << c.second.y << "\n";
  std::cout << "e\n";

  std::cout << "# Closest points (naive): " << n.first << " " << n.second
            << " (d=" << distance(n) << ")\n";
  std::cout << "# Closest points (di&co): " << c.first << " " << c.second
            << " (d=" << distance(c) << ")\n";
  return 0;
}
