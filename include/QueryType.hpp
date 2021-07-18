#pragma once

#include <cstdint>
#include <variant>
#include <iostream>

class QueryType
{
 public:
  class Unknown
  {
   public:
    uint16_t num;
    Unknown(const uint16_t);
  };

  class A
  {};

  std::variant<A, Unknown> type;

  QueryType(const uint16_t);

  auto to_num() const -> uint16_t;

  static auto from_num(const uint16_t) -> QueryType;

  friend auto operator<<(std::ostream&, const QueryType&) -> std::ostream&;
};