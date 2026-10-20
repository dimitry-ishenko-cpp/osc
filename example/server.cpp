#include <asio.hpp>
#include <functional>
#include <osc++.hpp>
#include <print>

using asio::ip::udp;

void print(const osc::value& value)
{
    switch (value.tag())
    {
    case 'i': std::print(" {}", value.to_int32()); break;
    case 'f': std::print(" {}", value.to_float()); break;
    case 's': std::print(" \"{}\"", value.to_string()); break;
    case 'b': std::print(" blob({} bytes)", value.to_blob().size()); break;
    case 'h': std::print(" {}", value.to_int64()); break;
    case 't':
        if (value.to_time() == osc::immed) std::print(" immediate");
        else std::print(" {:%F %T}", value.to_time());
        break;
    case 'd': std::print(" {}", value.to_double()); break;
    case 'c': std::print(" '{}'", value.to_char()); break;
    case 'T': std::print(" true"); break;
    case 'F': std::print(" false"); break;
    case 'N': std::print(" nil"); break;
    case 'I': std::print(" inf"); break;
    }
}

void print(const osc::message& message)
{
    std::print("{}", message.address());
    for (auto&& val : message.values()) print(val);
    std::print("\n");
}
 
void print(const osc::bundle& bundle)
{
    for (auto&& el : bundle.elements())
    {
        std::print("  ");
        if (el.is_message()) print(el.to_message());
        else print(el.to_bundle());
    }
}

int main()
{
    asio::io_context io;

    udp::endpoint local{ asio::ip::make_address("127.0.0.1"), 1984 };
    udp::socket socket{io};

    socket.open(udp::v4());
    socket.bind(local);

    std::function<void(const asio::error_code&)> callback = [&](const asio::error_code& ec)
    {
        if (ec) return;

        osc::packet packet{ static_cast<osc::int32>(socket.available()) };
        udp::endpoint remote;
        socket.receive_from(asio::buffer(packet.data(), packet.size()), remote);

        try
        {
            auto element = packet.parse();
            if (element.is_message())
            {
                auto message = element.to_message();
                std::print("Received message:\n");
                print(message);
            }
            else if (element.is_bundle())
            {
                auto bundle = element.to_bundle();
                std::print("Received bundle:\n");
                print(bundle);
            }

            socket.async_wait(udp::socket::wait_read, callback);
        }
        catch (std::invalid_argument& e)
        {
            std::print(stderr, "{}\n", e.what());
        }
    };

    socket.async_wait(udp::socket::wait_read, callback);

    io.run();
    return 0;
}
