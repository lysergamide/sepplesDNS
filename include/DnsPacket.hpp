#pragma once

#include <DnsHeader.hpp>
#include <DnsQuestion.hpp>
#include <DnsRecord.hpp>

#include <vector>

struct DnsPacket {
  DnsHeader                header;
  std::vector<DnsQuestion> questions;
  std::vector<DnsRecord>   answers;
  std::vector<DnsRecord>   authorities;
  std::vector<DnsRecord>   resources;

  DnsPacket(PacketBuffer& buffer);
};