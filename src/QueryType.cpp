#include <QueryType.hpp>

QueryType::QueryType() : type { QueryType::Unknown } {}

QueryType::QueryType(const uint16_t x)
{
  switch (x) {
  case 1: type = QueryType::A; break;
  default: type = QueryType::Unknown; break;
  }
}

/**
 * @brief pretty much just a cast to u16
 * @return uint16_t
 */
auto QueryType::to_num() const -> uint16_t { return type; }

/**
 * @brief get a Query type from a number
 * @param x
 * @return QueryType
 */
auto QueryType::from_num(const uint16_t x) -> QueryType { return QueryType(x); }