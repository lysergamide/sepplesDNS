#pragma once

#include <array>
#include <cstdint>
#include <string>

#include <sepplesDNS/DnsPacket/QueryType.hpp>

namespace sepplesDNS
{
class Record
{
 private:
  std::string            domain;
  std::array<uint8_t, 4> ipv4Addr;
  uint32_t               ttl;

  // used for Unknown records
  QueryType qtype;
  uint16_t  data_len;

 public:
  DnsRecord();
};
}  // namespace sepplesDNS