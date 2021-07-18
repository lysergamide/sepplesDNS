#pragma once

#include <PacketBuffer.hpp>
#include <QueryType.hpp>

#include <string>

class DnsQuestion
{
 private:
  std::string name;
  QueryType   qtype;

 public:
  template <class S, class QT>
  DnsQuestion(const S&& n, const QT&& q) : name { n }
                                         , qtype { q }
  {}

  template <class PB>
  DnsQuestion(PB&& buffer)
      : name { buffer.read_qname() }
      , qtype { QueryType::from_num(buffer.read_u16()) }
  {
    buffer.read_u16();
  }

  friend auto operator<<(std::ostream&, const DnsQuestion&) -> std::ostream&;
};