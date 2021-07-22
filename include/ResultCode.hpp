#pragma once
#include <fmt/format.h>

namespace ResultCode
{
enum Code {
  NOERROR,
  FORMERR,
  SERVFAIL,
  NXDOMAIN,
  NOTIMP,
  REFUSED,
};

auto from_num(const unsigned x) -> Code;
}  // namespace ResultCode

template <>
struct fmt::formatter<ResultCode::Code> : fmt::formatter<std::string_view> {
  template <typename FormatContext>
  auto format(const ResultCode::Code c, FormatContext& ctx)
  {
    auto str = std::string_view{ "" };

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