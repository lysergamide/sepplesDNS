#include <DnsPacket.hpp>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>

auto main() -> int
{
  try {
    auto pb = PacketBuffer {};
    auto fs = std::ifstream("response_packet.txt", std::ios_base::binary);

    std::copy(std::istream_iterator<char>(fs),
              std::istream_iterator<char>(),
              pb.buffer.begin());

    auto packet = DnsPacket(pb);
    std::cout << packet.header << '\n';
    for (auto& q : packet.questions)
      std::cout << q << '\n';
    for (auto& a : packet.answers)
      std::cout << a << '\n';
    for (auto& a : packet.authorities)
      std::cout << a << '\n';
    for (auto& r : packet.resources)
      std::cout << r << '\n';

  } catch (std::out_of_range& e) {
    std::cerr << e.what() << '\n';
  }
}