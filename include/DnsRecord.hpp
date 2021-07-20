#pragma once

#include <PacketBuffer.hpp>
#include <QueryType.hpp>

#include <array>
#include <string>
#include <variant>

/// @brief DNS record class
struct DnsRecord {
  std::string            domain;
  std::array<uint8_t, 4> ipv4Addr;
  uint32_t               ttl;

  // used for Unknown records
  QueryType qtype;
  uint16_t  data_len;

  DnsRecord(PacketBuffer& buffer);
};

template <> struct fmt::formatter<DnsRecord> : fmt::formatter<std::string> {
  template <typename FormatContext>
  auto format(const DnsRecord& r, FormatContext& ctx)
  {
    auto fstr = fmt::format("");

    switch (r.qtype.to_num()) {
    case QueryType::A: {
      auto ip = std::string {};
      for (size_t i = 0; i < 3; ++i)
        ip += std::to_string(r.ipv4Addr[i]) + ".";
      ip.append(std::to_string(r.ipv4Addr[3]));

      fstr = fmt::format(
        "DNS Record {{"
        "\n  Domain: {}"
        "\n  ipv4: {}"
        "\n}}",
        r.domain,
        ip);
      break;
    }

    default: {
      fstr = fmt::format(
        "DNS Record {{"
        "\n  Domain: {}"
        "\n  Query Type: {}"
        "\n  data_len: {}"
        "\n  ttl: {}",
        r.domain,
        r.qtype,
        r.data_len,
        r.ttl);
      break;
    }
    }

    return formatter<string>::format(fstr, ctx);
  }
};