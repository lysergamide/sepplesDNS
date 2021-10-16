#pragma once

#include <sepplesDNS/DnsPacket/Header.hpp>
#include <sepplesDNS/DnsPacket/Question.hpp>
#include <sepplesDNS/DnsPacket/Record.hpp>

namespace sepplesDNS
{
class DnsPacket
{
 private:
  Header                header;
  std::vector<Question> questions;
  std::vector<Record>   answers;
  std::vector<Record>   authorities;
  std::vector<Record>   resources;
};
}  // namespace sepplesDNS