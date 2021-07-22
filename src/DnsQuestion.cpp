#include <DnsQuestion.hpp>

/// @brief default construct a DnsQuestion
DnsQuestion::DnsQuestion() : name{ "" }, qtype{ QueryType::Unknown } {}

/// @brief construct a DnsQuestion from a name and query type
DnsQuestion::DnsQuestion(std::string_view n, const QueryType q)
    : name{ n }
    , qtype{ q }
{}

/// @brief extract a DnsQuestion from a byte buffer
DnsQuestion::DnsQuestion(ByteBuffer& buffer)
    : name{ buffer.read_qname() }
    , qtype{ QueryType::from_num(buffer.read_u16()) }
{
  buffer.read_u16();
}