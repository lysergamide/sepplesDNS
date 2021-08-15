#include <DnsRecord.hpp>

/// @brief Construct a new Dns Record object
DnsRecord::DnsRecord()
    : domain {""}
    , ipv4Addr {0}
    , ttl {0}
    , qtype {QueryType::Unknown}
    , data_len {0}
{}
/**
 * @brief Construct a new Dns Record object from a byte buffer
 * @tparam PB
 * @exception std::out_of_range can throw if there is a problem with reading
 * the buffer
 * @param buffer byte buffer
 */
DnsRecord::DnsRecord(ByteBuffer& buffer)
{
  domain = buffer.read_qname();
  qtype  = QueryType::from_num(buffer.read_u16());

  buffer.read_u16();

  ttl      = buffer.read_u32();
  data_len = buffer.read_u16();

  if (qtype.type != QueryType::Unknown) {
    const auto raw_addr = buffer.read_u32();
    for (auto i = 0; i < 4; ++i)
      ipv4Addr[3 - i] = (raw_addr >> (8 * i)) & 0xff;
  }
}
