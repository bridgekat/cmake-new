#include <print>
#include <span>
#include <string_view>

auto main(int argc, char* argv[]) -> int {
  for (auto argp: std::span(argv, argc)) {
    std::println("{}", std::string_view(argp));
  }
  return 0;
}
