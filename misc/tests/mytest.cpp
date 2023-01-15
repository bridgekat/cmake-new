#include <cassert>
#include <mylib.hpp>
#include "common.hpp"

auto main() -> int {
  val obj = MyClass();
  assert(obj.add(1, 2) == 3);
  return 0;
}
