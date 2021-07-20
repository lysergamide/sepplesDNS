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
    auto fstr = fmt::format("");

    switch (c) {
    case ResultCode::NOERROR: fstr = fmt::format("NOERROR"); break;
    case ResultCode::FORMERR: fstr = fmt::format("FORMERR"); break;
    case ResultCode::SERVFAIL: fstr = fmt::format("SERVFAIL"); break;
    case ResultCode::NXDOMAIN: fstr = fmt::format("NXDOMAIN"); break;
    case ResultCode::NOTIMP: fstr = fmt::format("NOTIMP"); break;
    case ResultCode::REFUSED: fstr = fmt::format("REFUSED"); break;
    }

    return formatter<string>::format(fstr, ctx);
  }
};