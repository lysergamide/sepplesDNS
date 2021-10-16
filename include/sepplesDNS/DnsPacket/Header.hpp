#pragma once
#include <cstdint>

namespace sepplesDNS
{

class ResultCode
{
 public:
  enum value : uint8_t {
    NOERROR,
    FORMERR,
    SERVFAIL,
    NXDOMAIN,
    NOTIMP,
    REFUSED,
    FORMERR,
  };
  ResultCode(uint8_t v) : val {v} {};
  operator uint8_t() const{ return val; };

 private:
  value val;
};

class Header
{
 private:
  uint16_t id;

  bool    recursionDesired;
  bool    truncatedMessage;
  bool    authoritativeAnswer;
  uint8_t opcode;

  ResultCode rescode;
  bool       checkingDisabled;
  bool       authedData;
  bool       z;
  bool       recursionAvailable;

  uint16_t questions;
  uint16_t answers;
  uint16_t authoritativeEntries;
  uint16_t resourceEntries;

 public:
  Header();
};

}  // namespace sepplesDNS