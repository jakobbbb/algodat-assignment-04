#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "closest.hpp"
#include "mergesort.hpp"

#define MAX_I 30

TEST_CASE("mergesort", "[mergesort]") {
  GIVEN("a vector of points") {
    std::vector<point> points = {
        {2.f, 1.f}, {0.f, -1.f}, {3.f, 0.f}, {-1.f, 3.f},
        {6.f, 6.f}, {4.f, 5.f},  {5.f, 4.f}, {1.f, 2.f},

    };
    WHEN("sorting by x") {
      std::vector<point> correct = {
          {-1.f, 3.f}, {0.f, -1.f}, {1.f, 2.f}, {2.f, 1.f},
          {3.f, 0.f},  {4.f, 5.f},  {5.f, 4.f}, {6.f, 6.f},
      };
      REQUIRE(mergesort_x(points) == correct);
    }
    WHEN("sorting by y") {
      std::vector<point> correct = {
          {0.f, -1.f}, {3.f, 0.f}, {2.f, 1.f}, {1.f, 2.f},
          {-1.f, 3.f}, {5.f, 4.f}, {4.f, 5.f}, {6.f, 6.f},
      };
      REQUIRE(mergesort_y(points) == correct);
    }
  }
}

TEST_CASE("closest points", "[closest_points]") {
  GIVEN("an empty vector of points") {
    auto p = random_points(0);
    REQUIRE(p.empty());
    REQUIRE_THROWS(closest(p));
    REQUIRE_THROWS(closest_naive(p));
  }
  GIVEN("a one-element vector of points") {
    auto p = random_points(1);
    REQUIRE(1 == p.size());
    REQUIRE_THROWS(closest(p));
    REQUIRE_THROWS(closest_naive(p));
  }
  GIVEN("a two-element vector of points") {
    auto p = random_points(2);
    REQUIRE(2 == p.size());
    REQUIRE(distance(closest_naive(p)) == distance(std::make_pair(p[0], p[1])));
    REQUIRE(distance(closest(p)) == distance(std::make_pair(p[0], p[1])));
  }
  GIVEN("n-element vectors of points") {
    for (int i = 3; i <= MAX_I; ++i) {
      std::cout << i << '\n';
      auto const p = random_points(i);
      REQUIRE(i == p.size());
      REQUIRE(distance(closest_naive(p)) == distance(closest(p)));
    }
  }
  GIVEN("n-element vectors of points with negative coordinates") {
    for (int i = 3; i <= MAX_I; ++i) {
      std::cout << i << '\n';
      auto p = random_points(i, {-42.23f, -23.42f}, {12.34f, 98.76f});
      REQUIRE(i == p.size());
      REQUIRE(distance(closest_naive(p)) == distance(closest(p)));
    }
  }
}
