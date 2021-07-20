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
struct fmt::formatter<ResultCode::Code> : fmt::formatter<std::string> {
  template <typename FormatContext>
  auto format(const ResultCode::Code c, FormatContext& ctx)
  {
    auto str = std::string { "" };

    switch (c) {
      case ResultCode::NOERROR: str = std::string { "NOERROR" }; break;
      case ResultCode::FORMERR: str = std::string { "FORMERR" }; break;
      case ResultCode::SERVFAIL: str = std::string { "SERVFAIL" }; break;
      case ResultCode::NXDOMAIN: str = std::string { "NXDOMAIN" }; break;
      case ResultCode::NOTIMP: str = std::string { "NOTIMP" }; break;
      case ResultCode::REFUSED: str = std::string { "REFUSED" }; break;
    }

    return fmt::formatter<std::string>::format(str, ctx);
  }
};