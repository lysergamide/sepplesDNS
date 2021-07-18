#pragma once

#include <QueryType.hpp>

#include <array>
#include <string>
#include <variant>

// template black magic for std::visit
template <class... Ts> struct overloaded : Ts... {
  using Ts::operator()...;
};
template <class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

/// @brief DNS record class
class DnsRecord
{
 private:
  struct Unknown {
    std::string domain   = "";
    uint16_t    qtype    = 0;
    uint16_t    data_len = 0;
    uint32_t    ttl      = 0;

    friend auto operator<<(std::ostream&, const DnsRecord::Unknown&)
      -> std::ostream&;
  };

  struct A {
    std::string            domain   = "";
    std::array<uint8_t, 4> ipv4Addr = { 0 };
    uint32_t               ttl      = 0;

    friend auto operator<<(std::ostream&, const DnsRecord::A&) -> std::ostream&;
  };

  std::variant<Unknown, A> record;

 public:
  /**
   * @brief Construct a new Dns Record object
   * @tparam PB
   * @exception std::out_of_range can throw if there is a problem with reading
   * the buffer
   * @param buffer packet buffer
   */
  template <class PB> DnsRecord(PB&& buffer)
  {
    const auto domain    = buffer.read_qname();
    const auto qtype_num = buffer.read_u16();
    const auto qtype     = QueryType::from_num(qtype_num);
    buffer.read_u16();
    const auto ttl      = buffer.read_u32();
    const auto data_len = buffer.read_u16();

    // what no pattern matching does to a mf

    std::visit(
      overloaded { [&](const QueryType::A& a) -> void {
                    const auto raw_addr   = buffer.read_u32();
                    auto       tmp_record = DnsRecord::A();

                    tmp_record.domain = domain;
                    for (auto i = 0; i < 4; ++i) {
                      tmp_record.ipv4Addr[3 - i] = (raw_addr >> (8 * i)) & 0xff;
                    }
                    tmp_record.ttl = ttl;
                    record         = tmp_record;
                  },
                   [&](const QueryType::Unknown& u) -> void {
                     buffer.step(data_len);
                     auto tmp_record = DnsRecord::Unknown();

                     tmp_record.domain   = domain;
                     tmp_record.qtype    = qtype_num;
                     tmp_record.data_len = data_len;
                     tmp_record.ttl      = ttl;

                     record = tmp_record;
                   } },
      qtype.type);
  }

  friend auto operator<<(std::ostream&, const DnsRecord&) -> std::ostream&;
};