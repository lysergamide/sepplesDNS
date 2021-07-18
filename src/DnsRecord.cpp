#include <DnsRecord.hpp>

#include <iostream>
#include <variant>

// debug info

auto operator<<(std::ostream& os, const DnsRecord& r) -> std::ostream&
{
  os << "<DNS Record: {\n";

  // ugly
  std::visit(overloaded { [&](const DnsRecord::A& a) -> void {
                           os << "  Domain: " << a.domain << '\n' << "  ipv4: ";
                           for (auto i = 0; i < 3; ++i)
                             os << a.ipv4Addr[i] << ".";
                           os << a.ipv4Addr[3] << '\n';
                         },
                          [&](const DnsRecord::Unknown& u) -> void {
                            os << "  Domain: " << u.domain << '\n'
                               << "  Query Type: " << u.qtype << '\n'
                               << "  data_len: " << u.data_len << '\n'
                               << "  ttl: " << u.ttl << '\n';
                          } },
             r.record);

  os << "}>";

  return os;
}