#pragma once

#include <fmt/format.h>

#include <cstdint>
#include <iostream>
#include <variant>

/// @brief a struct to handle query types
struct QueryType {
  enum qtype : uint16_t { Unknown = 0,
                          A };
  qtype type;

  QueryType();
  QueryType(const uint16_t);

  auto        to_num() const -> uint16_t;
  static auto from_num(const uint16_t) -> QueryType;

  operator uint16_t() const;
};

template <>
struct fmt::formatter<QueryType> : fmt::formatter<std::string_view> {
  auto
  format(const QueryType& q, format_context& ctx)
  {
    auto str = std::string_view {};
    switch (q.type) {
      case QueryType::A: str = "A"; break;
      default: str = "Unknown"; break;
    }

    return fmt::formatter<std::string_view>::format(fmt::format("{}", str),
                                                    ctx);
  }
};