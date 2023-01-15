#ifndef COMMON_HPP_
#define COMMON_HPP_

#include <cstddef>
#include <cstdint>
#include <iostream>

// Aliases.
#define val auto const
#define var auto

// Make sure to put these into the global scope.
using std::int8_t;
using std::int16_t;
using std::int32_t;
using std::int64_t;
using std::ptrdiff_t;

using std::uint8_t;
using std::uint16_t;
using std::uint32_t;
using std::uint64_t;
using std::size_t;

// Should be present in ISO C++23. Redefined due to `ms-vscode.cpptools` being unable to recognise the "uz" suffix.
// See: https://stackoverflow.com/questions/22346369/initialize-integer-literal-to-stdsize-t
// This definition should never be visible to the compiler, as user-defined literal suffixes without a
// leading underscore are considered ill-formed by the standard.
// See: https://en.cppreference.com/w/cpp/language/user_literal
#if __cpp_size_t_suffix < 202011L
constexpr auto operator"" uz(unsigned long long n) -> size_t { return n; }
#endif

// "Unreachable" mark.
[[noreturn]] inline auto unreachable(char const* file, int line, char const* func) -> void {
  std::cerr << "\"Unreachable\" code was reached: " << file << ":" << line << ", at function " << func << std::endl;
  std::terminate();
}
#define unreachable unreachable(__FILE__, __LINE__, static_cast<char const*>(__func__))

// "Unimplemented" mark.
[[noreturn]] inline auto unimplemented(char const* file, int line, char const* func) -> void {
  std::cerr << "\"Unimplemented\" code was called: " << file << ":" << line << ", at function " << func << std::endl;
  std::terminate();
}
#define unimplemented unimplemented(__FILE__, __LINE__, static_cast<char const*>(__func__))

#endif // COMMON_HPP_
