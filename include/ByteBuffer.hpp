#pragma once

#include <array>
#include <fstream>
#include <string>

/**
 * @brief Class for reading and writting packets
 */
class ByteBuffer
{
 private:
  size_t                   pos;
  std::array<uint8_t, 512> buffer;

  auto seek(const size_t) -> void;
  auto get(const size_t) const -> uint8_t;
  auto read() -> uint8_t;
  auto get_range(const size_t, const size_t) const -> std::string;

  auto write_u8(const uint8_t) -> void;
  auto write_u16(const uint16_t) -> void;
  auto write_u32(const uint32_t) -> void;
  auto write_qname(std::string_view) -> void;

  auto write(const DnsHeader&) -> void;
  auto write(const DnsQuestions&) -> void;
  auto write(const DnsRecord&) -> void;

 public:
  ByteBuffer();
  ByteBuffer(std::ifstream&);

  auto step(const size_t) -> void;
  auto get_pos() const -> size_t;
  auto read_u16() -> uint16_t;
  auto read_u32() -> uint32_t;
  auto read_qname() -> std::string;

  auto write(const DnsPacket&) -> void;
};
