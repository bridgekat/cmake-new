#include <cassert>
#include <cstdint>
#include <format>
#include <string>

import allocator;
using allocator::Allocator;

import matcher;
using matcher::match;

struct Thing {
  std::string first;
  std::uint32_t second;
};

auto main() -> int {
  auto alloc = Allocator<Thing>();
  auto p = alloc.emplace(Thing{"Hello", 233});
  assert(std::format("{} {}", p->first, p->second) == "Hello 233");
  return 0;
}
