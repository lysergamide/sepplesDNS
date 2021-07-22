#include <DnsPacket.hpp>

/// @brief default construct a DnsPacket
DnsPacket::DnsPacket()
    : header{}
    , questions{}
    , answers{}
    , authorities{}
    , resources{}
{}

/**
 * @brief Construct a new Dns Packet from a packet buffer
 * @param buffer
 */
DnsPacket::DnsPacket(ByteBuffer& buffer) : DnsPacket()
{
  header = DnsHeader(buffer);

  for (auto i = 0u; i < header.questions; ++i)
    questions.emplace_back(buffer);
  for (auto i = 0u; i < header.answers; ++i)
    answers.emplace_back(buffer);
  for (auto i = 0u; i < header.authoritative_entries; ++i)
    authorities.emplace_back(buffer);
  for (auto i = 0u; i < header.resource_entries; ++i)
    resources.emplace_back(buffer);
}

/**
 * @brief Construct a new Dns Packet object from a file stream
 * @param fs stream
 */
DnsPacket::DnsPacket(std::ifstream& fs) : DnsPacket{ ByteBuffer(fs) } {}