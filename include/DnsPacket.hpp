#pragma once

#include <DnsHeader.hpp>
#include <DnsQuestion.hpp>
#include <DnsRecord.hpp>

#include <fstream>
#include <vector>

/// @brief a class representing a dns packet
class DnsPacket
{
 private:
  DnsHeader                header;
  std::vector<DnsQuestion> questions;
  std::vector<DnsRecord>   answers;
  std::vector<DnsRecord>   authorities;
  std::vector<DnsRecord>   resources;

 public:
  DnsPacket();
  DnsPacket(ByteBuffer&);
  DnsPacket(ByteBuffer&&);
  DnsPacket(std::ifstream&);
  friend fmt::formatter<DnsPacket>;
};

template <>
struct fmt::formatter<DnsPacket> : fmt::formatter<std::string_view> {
  auto format(const DnsPacket& p, format_context& ctx)
  {
    const auto fstr = fmt::format("{} {} {} {} {}",
                                  p.header,
                                  fmt::join(p.questions, "\n"),
                                  fmt::join(p.answers, "\n"),
                                  fmt::join(p.authorities, "\n"),
                                  fmt::join(p.resources, "\n"));

    return fmt::formatter<std::string_view>::format(fstr, ctx);
  }
};