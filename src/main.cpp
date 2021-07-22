#include <DnsPacket.hpp>

#include <fmt/printf.h>

#include <fstream>

auto main() -> int
{
  using namespace std;
  using namespace fmt;

  try {
    auto fs = ifstream("D:/Projects/sepplesDNS/build/Debug/query_packet",
                       ios_base::binary);
    auto packet = DnsPacket(fs);

    print("{}", packet);

  } catch (out_of_range& e) {
    print(stderr, "{}\n", e.what());
  }
}