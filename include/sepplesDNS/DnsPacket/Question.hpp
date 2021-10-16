#pragma once

#include <string>

#include <sepplesDNS/DnsPacket/QueryType.hpp>

class Question
{
  std::string name;
  QueryType   qtype;

  DnsQuestion();
  DnsQuestion(std::string_view, const QueryType);
  DnsQuestion(ByteBuffer& buffer);
};