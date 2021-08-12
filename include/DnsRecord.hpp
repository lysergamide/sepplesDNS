#pragma once

#include <ByteBuffer.hpp>
#include <QueryType.hpp>

#include <array>
#include <variant>

/// @brief a struct representing a dns record
struct DnsRecord {
  std::string            domain;
  std::array<uint8_t, 4> ipv4Addr;
  uint32_t               ttl;

  // used for Unknown records
  QueryType qtype;
  uint16_t  data_len;

  DnsRecord();
  DnsRecord(ByteBuffer& buffer);
};

template <>
struct fmt::formatter<DnsRecord> : fmt::formatter<std::string_view> {
  auto format(const DnsRecord& r, format_context& ctx)
  {
    auto fstr = fmt::format("");

    switch (r.qtype.to_num()) {
      case QueryType::A: {
        fstr = fmt::format("DNS Record {{"
                           "\n  Query Type: {}"
                           "\n  Domain: {}"
                           "\n  ipv4: {}"
                           "\n  ttl: {}"
                           "\n}}",
                           r.qtype,
                           r.domain,
                           fmt::join(r.ipv4Addr, "."),
                           r.ttl);
        break;
      }

      default: {
        fstr = fmt::format("DNS Record {{"
                           "\n  Query Type: {}"
                           "\n  Domain: {}"
                           "\n  data_len: {}"
                           "\n  ttl: {}"
                           "\n}}",
                           r.qtype,
                           r.domain,
                           r.data_len,
                           r.ttl);
        break;
      }
    }

    return fmt::formatter<std::string_view>::format(fstr, ctx);
  }
};