#pragma once
#include <cstdint>

namespace sepplesDNS
{
class QueryType
{
 private:
  enum qtype : uint16_t {
    Unknown = 0,
    A,
  };

  qtype type;

 public:
  QueryType();
  QueryType(const uint16_t);

  auto toNum() const -> uint16_t;

  operator uint16_t() const;
};
}  // namespace sepplesDNS