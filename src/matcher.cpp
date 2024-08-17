module;
#include <variant>

export module matcher;
export namespace matcher {

/// "Pattern matching" on `std::variant`.
/// See: https://en.cppreference.com/w/cpp/utility/variant/visit
/// See: https://en.cppreference.com/w/cpp/language/aggregate_initialization
template <typename... Ts>
struct Visitor: Ts... {
  using Ts::operator()...;
};

/// Usage: `match(variant, [&](T v) { return ...; }, [&](T v) { return ...; }, ...)`
/// Return values of each lambda must have the same type.
template <typename T, typename... Ts>
constexpr auto match(T&& variant, Ts&&... lambdas) {
  return std::visit(Visitor<Ts...>{std::forward<Ts>(lambdas)...}, std::forward<T>(variant));
}

}
