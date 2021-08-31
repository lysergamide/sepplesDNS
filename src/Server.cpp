#include <Server.hpp>

#include <cstdlib>
#include <iostream>

using namespace boost;
using namespace boost::asio::ip;

Server::Server(asio::io_context& ctx, uint8_t port)
    : socket {ctx, udp::endpoint(udp::v4(), port)}
{
  do_receive();
}

auto
Server::do_receive() -> void
{
  socket.async_receive_from(
      asio::buffer(data, max_length),
      sender_endpoint,
      [this](auto ec, size_t bytes) {
        if (!ec && bytes > 0)
          do_send(bytes);
        else
          do_receive();
      });
}

auto
Server::do_send(size_t len) -> void
{
  socket.async_send_to(
      asio::buffer(data, len),
      sender_endpoint,
      [this](auto, auto) { do_receive();});
}