#pragma once

#include <ByteBuffer.hpp>
#include <QueryType.hpp>

#include <fmt/format.h>

struct DnsQuestion {
  std::string name;
  QueryType   qtype;

  DnsQuestion();
  DnsQuestion(std::string_view, const QueryType);
  DnsQuestion(ByteBuffer& buffer);
};

template <> struct fmt::formatter<DnsQuestion> : fmt::formatter<std::string_view> {
  template <typename FormatContext>
  auto format(const DnsQuestion& q, FormatContext& ctx)
  {
    const auto fstr = fmt::format("DNS Question: {{"
                                  "\n  name: {}"
                                  "\n  qtype: {}"
                                  "\n}}",
                                  q.name,
                                  q.qtype);

    return fmt::formatter<std::string_view>::format(fstr, ctx);
  }
};