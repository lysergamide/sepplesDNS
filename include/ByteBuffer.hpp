#pragma once

#include <array>
#include <fstream>
#include <string>

class DnsPacket;
struct DnsHeader;
struct DnsQuestion;
struct DnsRecord;

/**
 * @brief Class for reading and writting packets
 */
class ByteBuffer
{
 private:
  size_t                   pos;

  auto seek(const size_t) -> void;
  auto get(const size_t) const -> uint8_t;
  auto read() -> uint8_t;
  auto get_range(const size_t, const size_t) const -> std::string;

  auto write_u8(const uint8_t) -> void;
  auto write_u16(const uint16_t) -> void;
  auto write_u32(const uint32_t) -> void;
  auto write_qname(const std::string&) -> void;

  auto write(const DnsHeader&) -> void;
  auto write(const DnsQuestion&) -> void;
  auto write(const DnsRecord&) -> void;

 public:
  std::array<uint8_t, 512> buffer;

  ByteBuffer();
  ByteBuffer(std::ifstream&);

  auto step(const size_t) -> void;
  auto get_pos() const -> size_t;
  auto read_u16() -> uint16_t;
  auto read_u32() -> uint32_t;
  auto read_qname() -> std::string;

  auto write(DnsPacket&) -> void;
};
