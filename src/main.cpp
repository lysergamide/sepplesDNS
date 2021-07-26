#include <DnsPacket.hpp>

#include <fmt/printf.h>

#include <fstream>

auto main(int argv, char** argv) -> int
{
  using namespace std;
  using namespace fmt;
  if (argv < 2) {
    fmt::print(stderr, "No filepat");
    return 0;
  }

  try {
    auto fs = ifstream(argv[1], ios_base::binary);
    auto packet = DnsPacket(fs);

    print("{}", packet);

  } catch (out_of_range& e) {
    print(stderr, "{}\n", e.what());
  }
}