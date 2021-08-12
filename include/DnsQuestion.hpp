#pragma once

#include <ByteBuffer.hpp>
#include <QueryType.hpp>

#include <fmt/format.h>

/// @brief a struct representing a dns question
struct DnsQuestion {
  std::string name;
  QueryType   qtype;

  DnsQuestion();
  DnsQuestion(std::string_view, const QueryType);
  DnsQuestion(ByteBuffer& buffer);
};

template <>
struct fmt::formatter<DnsQuestion> : fmt::formatter<std::string_view> {
  auto format(const DnsQuestion& q, format_context& ctx)
  {
    const auto fstr = fmt::format("DNS Question: {{"
                                  "\n  Query Type: {}"
                                  "\n  name: {}"
                                  "\n}}",
                                  q.name,
                                  q.qtype);

    return fmt::formatter<std::string_view>::format(fstr, ctx);
  }
};