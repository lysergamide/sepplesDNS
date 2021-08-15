#include <QueryType.hpp>

/// @brief the default QueryType is Unknown
QueryType::QueryType()
    : type {QueryType::Unknown}
{}

/**
 * @brief Construct a new Query Type object
 * @param x the type as a u16
 */
QueryType::QueryType(const uint16_t x)
{
  switch (x) {
    case 1: type = QueryType::A; break;
    default: type = QueryType::Unknown; break;
  }
}

/**
 * @brief a cast to u16
 * @return uint16_t
 */
auto
QueryType::to_num() const -> uint16_t
{
  return type;
}

/**
 * @brief get a Query type from a number
 * @param x
 * @return QueryType
 */
auto
QueryType::from_num(const uint16_t x) -> QueryType
{
  return QueryType(x);
}