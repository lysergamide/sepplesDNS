cmake_minimum_required(VERSION 3.14)
project(sepplesDNS)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)
add_executable(
  sepplesDNS
  ./src/main.cpp
  ./src/DnsHeader.cpp
  ./src/DnsRecord.cpp
  ./src/DnsPacket.cpp
  ./src/DnsQuestion.cpp
  ./src/PacketBuffer.cpp
  ./src/ResultCode.cpp
  ./src/QueryType.cpp
)