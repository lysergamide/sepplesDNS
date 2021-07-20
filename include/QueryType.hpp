#pragma once

#include <fmt/format.h>

#include <cstdint>
#include <iostream>
#include <variant>

// struct for querytypes
struct QueryType {
  enum qtype { Unknown, A };
  qtype type;

  QueryType();
  QueryType(const uint16_t);

  auto        to_num() const -> uint16_t;
  static auto from_num(const uint16_t) -> QueryType;
};

template <> struct fmt::formatter<QueryType> : fmt::formatter<std::string> {
  template <typename FormatContext>
  auto format(const QueryType& q, FormatContext& ctx)
  {
    auto str = std::string {};
    switch (q.type) {
    case QueryType::A: str = "A"; break;
    default: str = "Unknown"; break;
    }

    return fmt::formatter<std::string>::format(fmt::format("{}", str), ctx);
  }
};