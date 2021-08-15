#pragma once

#include <ByteBuffer.hpp>
#include <ResultCode.hpp>

#include <fmt/format.h>

/// @brief struct representing a dns header
struct DnsHeader {
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

  DnsHeader();
  DnsHeader(ByteBuffer&);
};

// fmt thing
template <>
struct fmt::formatter<DnsHeader> : fmt::formatter<std::string_view> {
  auto
  format(const DnsHeader& h, format_context& ctx)
  {
    const auto fstr = fmt::format(
        "DNS Header: {{"
        "\n  id: {}"
        "\n  recursion desired: {}"
        "\n  truncated_message: {}"
        "\n  authoritative_answer: {}"
        "\n  opcode: {}"
        "\n  response: {}"
        "\n  rescode: {}"
        "\n  checking_disabled: {}"
        "\n  authed_data: {}"
        "\n  z: {}"
        "\n  recursion_available: {}"
        "\n  questions: {}"
        "\n  answers: {}"
        "\n  authoritative_entries: {}"
        "\n  resource_entries: {}"
        "\n}}",
        h.id,
        h.recursion_desired,
        h.truncated_message,
        h.authoritative_answer,
        h.opcode,
        h.response,
        h.rescode,
        h.checking_disabled,
        h.authed_data,
        h.z,
        h.recursion_available,
        h.questions,
        h.answers,
        h.authoritative_entries,
        h.resource_entries);

    return fmt::formatter<std::string_view>::format(fstr, ctx);
  }
};