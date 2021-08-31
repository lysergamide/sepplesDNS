#include <DnsPacket.hpp>

#include <fmt/printf.h>

#include <fstream>

using namespace std;
using namespace fmt;

auto
main(int argc, char** argv) -> int
{
  auto qname = "google.com"s;
  auto qtype = QueryType::A;

  /*
  if (argc < 2) {
    print(stderr, "No filepath");
    return 0;
  }

  try {
    auto fs     = ifstream(argv[1], ios_base::binary);
    auto packet = DnsPacket {fs};

    print("{}", packet);

  } catch (out_of_range& e) {
    print(stderr, "{}\n", e.what());
  }
  */
}