#include <PacketBuffer.hpp>

#include <iostream>
#include <stdexcept>

/// @param step amount to increment #pos by
auto PacketBuffer::step(const size_t step) -> void { pos += step; }
/// @param next_pos position to move #pos to
auto PacketBuffer::seek(const size_t next_pos) -> void { pos = next_pos; }

/**
 * @brief read a byte #pos is incremented
 * @exception std::out_of_range
 * @return uint8_t
 */
auto PacketBuffer::read() -> uint8_t
{
  if (pos >= 512)
    throw std::out_of_range("#pos out of bounds");

  return buffer[pos++];
}

/**
 * @brief read a byte at an arbitrary location
 * @param i index to read from
 * @exception std::out_of_range
 * @return uint8_t
 */
auto PacketBuffer::get(size_t i) const -> uint8_t
{
  if (i >= 512)
    throw std::out_of_range("index out of bounds");

  return buffer[i];
}

/**
 * @brief get a string view from our buffer
 * @param start starting position
 * @param size  length of substring
 * @exception std::out_of_range
 * @return std::string_view
 */
auto PacketBuffer::get_range(const size_t start, const size_t size) const
  -> std::string_view
{
  if (start + size >= 512)
    throw std::out_of_range("range out of bounds");

  return std::string_view(reinterpret_cast<const char*>(&buffer[start]), size);
}

/// @brief construct a new PacketBuffer
PacketBuffer::PacketBuffer() : buffer { 0 }, pos { 0 } {};
/// @return #pos
auto PacketBuffer::get_pos() const -> size_t { return pos; }

/**
 * @brief read two bytes, #pos is incremented
 * @exception std::out_of_range
 * @return uint32_t
 */
auto PacketBuffer::read_u16() -> uint16_t
{
  const auto a = uint16_t { read() };
  const auto b = uint16_t { read() };
  return (a << 8) | b;
}

/**
 * @brief read four bytes, #pos is incremented
 * @exception std::out_of_range
 * @return uint32_t
 */
auto PacketBuffer::read_u32() -> uint32_t
{
  auto ret = uint32_t { 0 };

  for (auto i = 0; i < 4; i++) {
    ret <<= 8;
    ret |= read();
  }

  return ret;
}

/**
 * @brief read a query name (domain)
 * @return std::string the domain name
 */
auto PacketBuffer::read_qname() -> std::string
{
  const auto MAX_JUMPS = 5;

  auto p      = pos;  // duplicate pointer to handle jumps
  auto jumps  = 0;
  auto jumped = false;
  auto delim  = std::string { "" };
  auto ret    = std::string { "" };  // string to be returned

  for (;;) {
    // guards against malicious packets
    if (jumps > MAX_JUMPS)
      throw std::out_of_range("Packet exceeded maximum number of jumps");

    // check if length byte is a jump instruction
    auto len = get(p);
    if ((len & 0xc0) == 0xc0) {
      // update buffer position, only needs to be done the first time we jump
      if (!jumped)
        seek(p + 2);

      p      = ((static_cast<uint16_t>(len) ^ 0xc0) << 8) | get(p + 1);
      jumped = true;
      ++jumps;
    } else {
      ++p;

      if (len == 0)
        break;  // strings are null terminated

      ret.append(delim);
      ret.append(get_range(p, len));
      delim = ".";  // start with no delimiter then add dots between subdomains
      p += len;
    }
  }

  if (!jumped)
    seek(p);

  return ret;
}
