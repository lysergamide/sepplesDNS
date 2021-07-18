#include <DnsQuestion.hpp>

auto operator<<(std::ostream& os, const DnsQuestion& q) -> std::ostream&
{
  os << "<DNS Question: {\n"
     << "  Name: " << q.name << '\n'
     << "  Query type: " << q.qtype << '\n'
     << "}>";
  return os;
}