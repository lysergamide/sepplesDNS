#include <DnsPacket.hpp>

#include <fmt/printf.h>

#include <fstream>

auto main(int argc, char** argv) -> int
{
  using namespace std;
  using namespace fmt;

  if (argc < 2) {
    fmt::print(stderr, "No filepat");
    return 0;
  }

  try {
    auto fs     = ifstream(argv[1]);
    auto packet = DnsPacket(fs);

    print("{}", packet);

  } catch (out_of_range& e) {
    print(stderr, "{}\n", e.what());
  }
}