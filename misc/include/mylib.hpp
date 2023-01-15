#ifndef MYLIB_HPP_
#define MYLIB_HPP_

#include <cstddef>
#include <cstdint>

class MyClass {
public:
  auto add(std::int32_t a, std::int32_t b) const -> std::int32_t;
};

#endif // MYLIB_HPP_
