#pragma once

#include <array>
#include <string>

/**
 * @brief Class for holding and processing packets
 */
class ByteBuffer
{
 private:
  size_t pos;

  auto seek(const size_t) -> void;
  auto get(const size_t) const -> uint8_t;
  auto read() -> uint8_t;
  auto get_range(const size_t, const size_t) const -> std::string_view;

 public:
  std::array<uint8_t, 512> buffer;

  ByteBuffer();

  auto step(const size_t) -> void;
  auto get_pos() const -> size_t;
  auto read_u16() -> uint16_t;
  auto read_u32() -> uint32_t;
  auto read_qname() -> std::string;
};