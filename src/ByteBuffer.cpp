#include <ByteBuffer.hpp>

#include <iterator>
#include <stdexcept>

/// @param next_pos position to move #pos to
auto ByteBuffer::seek(const size_t next_pos) -> void { pos = next_pos; }

/**
 * @brief read a byte #pos is incremented
 * @exception std::out_of_range
 * @return uint8_t
 */
auto ByteBuffer::read() -> uint8_t
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
auto ByteBuffer::get(size_t i) const -> uint8_t
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
auto ByteBuffer::get_range(const size_t start, const size_t size) const
  -> std::string
{
  if (start + size >= 512)
    throw std::out_of_range("range out of bounds");

  return std::string(buffer.begin() + start, buffer.begin() + start + size);
}

/// @brief construct a new ByteBuffer
ByteBuffer::ByteBuffer() : buffer{ 0 }, pos{ 0 } {};

/**
 * @brief Construct a new Byte Buffer object from a file
 * @param fs file stream
 */
ByteBuffer::ByteBuffer(std::ifstream& fs) : ByteBuffer()
{
  std::copy(std::istream_iterator<uint8_t>(fs),
            std::istream_iterator<uint8_t>(),
            buffer.begin());
}

/// @param step amount to increment #pos by
auto ByteBuffer::step(const size_t step) -> void { pos += step; }
/// @return #pos
auto ByteBuffer::get_pos() const -> size_t { return pos; }

/**
 * @brief read two bytes, #pos is incremented
 * @exception std::out_of_range
 * @return uint32_t
 */
auto ByteBuffer::read_u16() -> uint16_t
{
  const auto a = uint16_t{ read() };
  const auto b = uint16_t{ read() };
  return (a << 8) | b;
}

/**
 * @brief read four bytes, #pos is incremented
 * @exception std::out_of_range
 * @return uint32_t
 */
auto ByteBuffer::read_u32() -> uint32_t
{
  auto ret = uint32_t{ 0 };

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
auto ByteBuffer::read_qname() -> std::string
{
  const auto MAX_JUMPS = 5;  // prevent inf loop from malicious packets

  auto p      = pos;  // duplicate pointer to handle jumps
  auto jumps  = 0;
  auto jumped = false;
  auto delim  = std::string_view{ "" };
  auto ret    = std::string{ "" };  // string to be returned

  for (;;) {
    if (jumps > MAX_JUMPS)
      throw std::out_of_range("Packet exceeded maximum number of jumps");

    auto len = get(p);

    // jump instruction
    if ((len & 0xc0) == 0xc0) {
      if (!jumped)
        seek(p + 2);

      const auto b1 = uint16_t{ ((static_cast<uint16_t>(len) ^ 0xc0u) << 8) };
      const auto b2 = uint16_t{ get(p + 1) };

      p      = b1 | b2;
      jumped = true;
      ++jumps;
    } else {
      ++p;
      if (!len)
        break;

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
