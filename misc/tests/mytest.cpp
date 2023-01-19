#include <cassert>
#include <mylib.hpp>
#include "common.hpp"

#define val auto const
#define var auto

auto main() -> int {
  val obj = MyClass();
  assert(obj.add(1, 2) == 3);
  return 0;
}
