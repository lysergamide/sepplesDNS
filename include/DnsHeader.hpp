#pragma once

#include <ResultCode.hpp>

#include <cstdint>
#include <iostream>

class DnsHeader
{
 public:
  uint16_t id;

  bool    recursion_desired;
  bool    truncated_message;
  bool    authoritative_answer;
  uint8_t opcode;
  bool    response;

  ResultCode::Code rescode;
  bool             checking_disabled;
  bool             authed_data;
  bool             z;
  bool             recursion_available;

  uint16_t questions;
  uint16_t answers;
  uint16_t authoritative_entries;
  uint16_t resource_entries;

 public:
  DnsHeader();

  /**
   * @brief Construct a new Dns Header object from a PacketBuffer
   *
   * @tparam PB a packet buffer
   * @exception std::out_of_range if there is a problem reading the buffer
   * @param buffer
   */
  template <class PB> DnsHeader(PB&& buffer) : id { buffer.read_u16() }
  {
    const auto flags = buffer.read_u16();
    const auto upper = flags >> 8;
    const auto lower = flags & 0xff;

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

    questions             = buffer.read_u16();
    answers               = buffer.read_u16();
    authoritative_entries = buffer.read_u16();
    resource_entries      = buffer.read_u16();
  }

  friend auto operator<<(std::ostream&, const DnsHeader&) -> std::ostream&;
};