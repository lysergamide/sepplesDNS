#include <DnsHeader.hpp>
#include <DnsPacket.hpp>

#include <fmt/printf.h>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>

using namespace std;
using namespace fmt;

auto main() -> int
{

  try {
    auto pb = PacketBuffer {};
    auto fs = ifstream("response_packet.txt", ios_base::binary);

    copy(istream_iterator<char>(fs),
         istream_iterator<char>(),
         pb.buffer.begin());

    auto packet = DnsPacket(pb);
    print("{}\n", packet.header);
    for (auto& q : packet.questions)
      print("{}\n", q);

    for (const auto& r :
         { packet.answers, packet.authorities, packet.resources }) {
      for (const auto& x : r)
        print("{}\n", x);
    }
    //    for (auto& a : packet.answers)
    //      std::cout << a << '\n';
    //    for (auto& a : packet.authorities)
    //      std::cout << a << '\n';
    //    for (auto& r : packet.resources)
    //      std::cout << r << '\n';

  } catch (out_of_range& e) {
    cerr << e.what() << '\n';
  }
}