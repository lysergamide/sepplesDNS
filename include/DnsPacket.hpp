#pragma once

#include <DnsHeader.hpp>
#include <DnsQuestion.hpp>
#include <DnsRecord.hpp>

#include <vector>

class DnsPacket
{
 public:
  DnsHeader                header      = {};
  std::vector<DnsQuestion> questions   = {};
  std::vector<DnsRecord>   answers     = {};
  std::vector<DnsRecord>   authorities = {};
  std::vector<DnsRecord>   resources   = {};

  template <class PB>
  DnsPacket(PB&& buffer)
      : header { buffer }
      , questions {}
      , answers {}
      , authorities {}
      , resources {}
  {
    for (auto i = 0u; i < header.questions; ++i)
      questions.emplace_back(buffer);
    for (auto i = 0u; i < header.answers; ++i)
      answers.emplace_back(buffer);
    for (auto i = 0u; i < header.authoritative_entries; ++i)
      authorities.emplace_back(buffer);
    for (auto i = 0u; i < header.resource_entries; ++i)
      resources.emplace_back(buffer);
  }
};