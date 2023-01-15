#include <tuple>
#include <array>
#include "common.hpp"

auto main() -> int {
  val tup = std::tuple(500, 6.4, 1);
  val[x, y, z] = tup;
  std::cout << "The values of x, y, z are: " << x << ", " << y << ", " << z << std::endl;

  val t = std::tuple<int32_t, float, int16_t>(500, 6.4, 1);
  val five_hundred = std::get<0>(t);
  val six_point_four = std::get<1>(t);
  val one = std::get<2>(t);
  std::cout << five_hundred << ", " << six_point_four << ", " << one << std::endl;

  val a = std::array{1, 2, 3, 4, 5};
  std::cout << "Please enter an array index." << std::endl;
  var index = 0uz;
  std::cin >> index;
  val element = a[index];
  std::cout << "The value of the element at index " << index << " is: " << element << std::endl;

  return 0;
}
