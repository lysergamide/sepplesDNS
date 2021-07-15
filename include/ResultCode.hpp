#pragma once

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