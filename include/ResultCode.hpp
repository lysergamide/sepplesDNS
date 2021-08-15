#pragma once
#include <fmt/format.h>

namespace ResultCode
{
enum Code : uint8_t {
  NOERROR,
  FORMERR,
  SERVFAIL,
  NXDOMAIN,
  NOTIMP,
  REFUSED,
};

auto from_num(const uint8_t x) -> Code;
}  // namespace ResultCode

template <>
struct fmt::formatter<ResultCode::Code> : fmt::formatter<std::string_view> {
  auto
  format(const ResultCode::Code c, format_context& ctx)
  {
    auto str = std::string_view {""};

    switch (c) {
      case ResultCode::NOERROR: str = "NOERROR"; break;
      case ResultCode::FORMERR: str = "FORMERR"; break;
      case ResultCode::SERVFAIL: str = "SERVFAIL"; break;
      case ResultCode::NXDOMAIN: str = "NXDOMAIN"; break;
      case ResultCode::NOTIMP: str = "NOTIMP"; break;
      case ResultCode::REFUSED: str = "REFUSED"; break;
    }

    return fmt::formatter<std::string_view>::format(str, ctx);
  }
};