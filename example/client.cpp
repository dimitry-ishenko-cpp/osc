#include <asio.hpp>
#include <osc++.hpp>
#include <print>

using asio::ip::udp;

int main()
{
    asio::io_context io;

    udp::endpoint remote{ asio::ip::make_address("127.0.0.1"), 1984 };
    udp::socket socket{io};

    socket.open(udp::v4());

    osc::message message{ "/abc/def/ghi" };
    message << 123 << 456 << 789;

    std::print("Sending message\n");
    auto packet = message.to_packet();
    socket.send_to(asio::buffer(packet.data(), packet.size()), remote);

    osc::bundle bundle;
    bundle << (osc::message{ "/a/b/c" } << 1 << 2 << 3)
           << (osc::message{ "/1/2/3" } << 'a' << 'b' << 'c');

    std::print("Sending bundle\n");
    auto packet_2 = bundle.to_packet();
    socket.send_to(asio::buffer(packet_2.data(), packet_2.size()), remote);

    return 0;
}
