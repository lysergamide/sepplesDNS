#include <DnsQuestion.hpp>

DnsQuestion::DnsQuestion(std::string_view n, const QueryType q)
    : name { n }
    , qtype { q }
{}

DnsQuestion::DnsQuestion(PacketBuffer& buffer)
    : name { buffer.read_qname() }
    , qtype { QueryType::from_num(buffer.read_u16()) }
{
  buffer.read_u16();
}