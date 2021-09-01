#include <DnsPacket.hpp>

#include <boost/asio.hpp>
#include <fmt/printf.h>

#include <fstream>

using namespace std;
using namespace fmt;
using namespace boost;
using namespace boost::asio::ip;

auto
main(int argc, char** argv) -> int
{
  auto packet  = DnsPacket {};
  auto req_buf = ByteBuffer {};
  auto res_buf = ByteBuffer {};

  packet.header.id                = 6666;
  packet.header.questions         = 1;
  packet.header.recursion_desired = true;
  packet.questions.emplace_back("google.com"s, QueryType::A);

  req_buf.write(packet);

  try {
    auto ctx       = asio::io_context {};
    auto sock      = udp::socket {ctx, udp::endpoint {udp::v4(), 43210}};
    auto end_point = udp::endpoint {make_address("8.8.8.8"), 53};

    sock.send_to(
        asio::buffer(req_buf.buffer, req_buf.get_pos() + 1),
        end_point);

    sock.receive_from(
        asio::buffer(res_buf.buffer),
        end_point);

  } catch (std::exception& e) {
    print(stderr, "{}\n", e.what());
  }
}