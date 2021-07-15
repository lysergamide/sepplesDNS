#include <ResultCode.hpp>

namespace ResultCode
{
auto from_num(const unsigned x) -> Code
{
  return (x > 5) ? NOERROR : static_cast<Code>(x);
}
}  // namespace ResultCode