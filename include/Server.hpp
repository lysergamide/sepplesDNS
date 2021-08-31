#include <boost/asio.hpp>

class Server
{
 private:
  boost::asio::ip::udp::socket   socket;
  boost::asio::ip::udp::endpoint sender_endpoint;

  static const size_t max_length = 1024;

  std::array<uint8_t, max_length> data;

 public:
  Server(boost::asio::io_context&, uint8_t);
  auto do_receive() -> void;
  auto do_send(size_t) -> void;
};