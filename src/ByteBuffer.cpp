#include <ByteBuffer.hpp>
#include <DnsHeader.hpp>
#include <DnsPacket.hpp>
#include <DnsQuestion.hpp>
#include <DnsRecord.hpp>

#include <iterator>
#include <sstream>
#include <stdexcept>

/// @param next_pos position to move #pos to
auto
ByteBuffer::seek(const size_t next_pos) -> void
{
  pos = next_pos;
}

/**
 * @brief read a byte #pos is incremented
 * @exception std::out_of_range
 * @return uint8_t
 */
auto
ByteBuffer::read() -> uint8_t
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
auto
ByteBuffer::get(size_t i) const -> uint8_t
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
auto
ByteBuffer::get_range(const size_t start, const size_t size) const
    -> std::string
{
  if (start + size >= 512)
    throw std::out_of_range("range out of bounds");

  return std::string {buffer.begin() + start, buffer.begin() + start + size};
}

/// @brief construct a new ByteBuffer
ByteBuffer::ByteBuffer()
    : buffer {0}
    , pos {0} {};

/**
 * @brief Construct a new Byte Buffer object from a file
 * @param fs file stream
 */
ByteBuffer::ByteBuffer(std::ifstream& fs)
    : ByteBuffer()
{
  std::copy(std::istreambuf_iterator<char>(fs),
            std::istreambuf_iterator<char>(),
            buffer.begin());
}

/// @param step amount to increment #pos by
auto
ByteBuffer::step(const size_t step) -> void
{
  pos += step;
}
/// @return #pos
auto
ByteBuffer::get_pos() const -> size_t
{
  return pos;
}

/**
 * @brief read two bytes, #pos is incremented
 * @exception std::out_of_range
 * @return uint32_t
 */
auto
ByteBuffer::read_u16() -> uint16_t
{
  const auto a = static_cast<uint16_t>(read());
  const auto b = static_cast<uint16_t>(read());
  return (a << 8) | b;
}

/**
 * @brief read four bytes, #pos is incremented
 * @exception std::out_of_range
 * @return uint32_t
 */
auto
ByteBuffer::read_u32() -> uint32_t
{
  auto ret = uint32_t {0};

  for (auto i = 0; i < 4; i++) {
    ret <<= 8;
    ret |= read();
  }

  return ret;
}

/**
 * @brief read a query name (domain name)
 * @return std::string the domain name
 */
auto
ByteBuffer::read_qname() -> std::string
{
  const auto MAX_JUMPS = 5;  // prevent inf loop from malicious packets

  auto p      = pos;  // duplicate pointer to handle jumps
  auto jumps  = 0;
  auto jumped = false;
  auto delim  = std::string_view {""};
  auto ret    = std::string {""};  // string to be returned

  for (;;) {
    if (jumps > MAX_JUMPS)
      throw std::out_of_range("Packet exceeded maximum number of jumps");

    auto len = get(p);

    // jump instruction
    if ((len & 0xc0) == 0xc0) {
      if (!jumped)
        seek(p + 2);

      const auto b1 = uint16_t {((static_cast<uint16_t>(len) ^ 0xc0u) << 8)};
      const auto b2 = uint16_t {get(p + 1)};

      p      = b1 | b2;
      jumped = true;
      ++jumps;

    } else {

      ++p;
      if (!len)  // strings end with a 0 byte
        break;

      ret.append(delim);
      ret.append(get_range(p, len));
      delim = ".";  // start with no delimiter then add dots between
                    // subdomains
      p += len + 1;
    }
  }

  if (!jumped)
    seek(p);

  return ret;
}

/// @brief write a byte to the buffer
auto
ByteBuffer::write_u8(uint8_t x) -> void
{
  if (pos >= 512)
    throw std::out_of_range("Attempting to write out of bounds");

  buffer[pos++] = x;
}

/// @brief write two bytes to the buffer
auto
ByteBuffer::write_u16(uint16_t x) -> void
{
  write_u8(static_cast<uint8_t>(x >> 8));
  write_u8(static_cast<uint8_t>(x & 0xf));
}

/// @brief write four bytes to the buffer
auto
ByteBuffer::write_u32(uint32_t x) -> void
{
  for (int i = 24; i >= 0; i -= 8)
    write_u8(static_cast<uint8_t>((x >> i) & 0xf));
}

/// helper function
auto
ByteBuffer::write_qname(const std::string& str) -> void
{
  auto ss = std::stringstream {str};

  // goes through the substrings seperated by a '.'
  for (auto label = std::string {}; std::getline(ss, label, '.');) {
    if (label.size() > 0x3f)
      throw std::out_of_range("Label exceeds 63 chars");

    write_u8(static_cast<uint8_t>(label.size()));

    for (const auto c : label)
      write_u8(c);

    write_u8(0);
  }
}

/**
 * These helper overloads need to be called in a specific order since they
 * mutate the buffers #pos
 */

/**
 * @brief write a dns header to the buffer
 * @param h header
 */
auto
ByteBuffer::write(const DnsHeader& h) -> void
{
  write_u16(h.id);
  write_u8(h.recursion_desired
           | h.truncated_message << 1
           | h.authoritative_answer << 2
           | h.opcode << 3
           | h.truncated_message << 7);
  write_u8(h.rescode
           | h.checking_disabled << 4
           | h.authed_data << 5
           | h.z << 6
           | h.recursion_available << 7);
  write_u16(h.questions);
  write_u16(h.answers);
  write_u16(h.authoritative_entries);
  write_u16(h.resource_entries);
}

/**
 * @brief write a dns question to the buffer
 * @param q dns question
 */
auto
ByteBuffer::write(const DnsQuestion& q) -> void
{
  write_qname(q.name);
  write_u16(q.qtype);
  write_u16(1);
}

/**
 * @brief write a dns record to the buffer
 * @param r dns record
 * 
 * TODO: this might need to change and return something
 */
auto
ByteBuffer::write(const DnsRecord& r) -> void
{
  switch (r.qtype) {
    case QueryType::A:
      write_qname(r.domain);
      write_u16(r.qtype);
      write_u16(1);
      write_u32(r.ttl);
      write_u16(4);
      for (const auto x : r.ipv4Addr)
        write_u8(x);
      break;

    default:
      fmt::print("Skipping record: {}", r);
      break;
  }
}

/**
 * @brief write the contents of a DnsPacket to the buffer
 * @param p the packet to write, may mutate #p.header
 */
auto
ByteBuffer::write(DnsPacket& p) -> void
{
  p.header.questions             = p.questions.size();
  p.header.answers               = p.answers.size();
  p.header.authoritative_entries = p.authorities.size();
  p.header.resource_entries      = p.resources.size();

  write(p.header);
  for (const auto& q : p.questions)
    write(q);
  for (const auto& records : {p.answers, p.authorities, p.resources})
    for (const auto& r : records)
      write(r);
}