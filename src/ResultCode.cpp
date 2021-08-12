#include <ResultCode.hpp>

namespace ResultCode
{
/**
 * @brief get a ResultCode from a u8
 * @param x u8 representing a ResultCode
 * @return ResultCode::Code
 */
auto from_num(const unsigned x) -> Code
{
  return (x > 5) ? NOERROR : static_cast<Code>(x);
}
}  // namespace ResultCode