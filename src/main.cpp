#include <DnsPacket.hpp>

#include <fmt/printf.h>

#include <algorithm>
#include <fstream>
#include <iterator>

auto main() -> int
{
  using namespace std;
  using namespace fmt;

  try {
    auto pb = ByteBuffer {};
    auto fs = ifstream("query_packet.txt", ios_base::binary);

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

  } catch (out_of_range& e) {
    cerr << e.what() << '\n';
  }
}