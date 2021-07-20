#include <DnsPacket.hpp>

DnsPacket::DnsPacket(ByteBuffer& buffer)
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
