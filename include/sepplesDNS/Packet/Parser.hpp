#pragma once

#include <array>
#include <memory>
#include <sepplesDNS/DnsPacket/DnsPacket.hpp>

namespace sepplesDNS::Packet
{
using Packet = std::array<uint8_t, 1024>;

auto parse(const Packet& p) -> std::unique_ptr<DnsPacket>;
auto write(const DnsPacket& p) -> std::unique_ptr<Packet>;
}  // namespace sepplesDNS::Packet