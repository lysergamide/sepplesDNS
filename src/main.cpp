#include <DnsHeader.hpp>

#include <iostream>

auto main() -> int
{
  auto head = std::make_unique<DnsHeader>();
  std::cout << *head << '\n';
}