#include <DnsHeader.hpp>

/// @brief default constructor
DnsHeader::DnsHeader()
    : id{ 0u }
    , recursion_desired{ false }
    , truncated_message{ false }
    , authoritative_answer{ false }
    , opcode{ 0u }
    , response{ false }
    , rescode{ ResultCode::NOERROR }
    , checking_disabled{ false }
    , authed_data{ false }
    , z{ false }
    , recursion_available{ false }
    , questions{ 0u }
    , answers{ 0u }
    , authoritative_entries{ 0u }
    , resource_entries{ 0u }
{}

/**
 * @brief Construct a new Dns Header object from a ByteBuffer
 *
 * @tparam PB a packet buffer
 * @exception std::out_of_range if there is a problem reading the buffer
 * @param buffer
 */
DnsHeader::DnsHeader(ByteBuffer& buffer) : DnsHeader()
{
  id = buffer.read_u16();

  const auto flags = buffer.read_u16();
  const auto upper = static_cast<uint8_t>(flags >> 8);
  const auto lower = static_cast<uint8_t>(flags & 0xff);

  recursion_desired    = upper & 1;
  truncated_message    = (upper >> 1) & 1;
  authoritative_answer = (upper >> 2) & 1;
  opcode               = (upper >> 3) & 0xf;
  response             = (upper >> 7) & 1;

  rescode             = ResultCode::from_num(lower & 0xf);
  checking_disabled   = (lower >> 4) & 1;
  authed_data         = (lower >> 5) & 1;
  z                   = (lower >> 6) & 1;
  recursion_available = (lower >> 7) & 1;

  // records
  questions             = buffer.read_u16();
  answers               = buffer.read_u16();
  authoritative_entries = buffer.read_u16();
  resource_entries      = buffer.read_u16();
}