#include <QueryType.hpp>

// template black magic for std::visit
template <class... Ts> struct overloaded : Ts... {
  using Ts::operator()...;
};
template <class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

QueryType::Unknown::Unknown(const uint16_t x) : num { x } {}

QueryType::QueryType(const uint16_t x)
{
  switch (x) {
  case 1: type = A {}; break;
  default: type = Unknown { x }; break;
  };
}

/**
 * @brief convert a query type to its number
 * @return uint16_t
 */
auto QueryType::to_num() const -> uint16_t
{
  return std::visit(
    overloaded { [](const A& a) -> uint16_t { return 1; },
                 [](const Unknown& u) -> uint16_t { return u.num; } },
    type);
}

/**
 * @brief get a Query type from a number
 * @param x
 * @return QueryType
 */
auto QueryType::from_num(const uint16_t x) -> QueryType { return QueryType(x); }

auto operator<<(std::ostream& os, const QueryType& qt) -> std::ostream&
{
  os << std::visit(
    overloaded {
      [](const QueryType::A& a) -> std::string { return "A"; },
      [](const QueryType::Unknown& u) -> std::string { return "Unknown"; } },
    qt.type);

  return os;
}