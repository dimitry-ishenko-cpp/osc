# osc++ – an OSC Library for C++

The **osc++** library allows one to easily create and parse [OSC (Open Sound Control)](https://opensoundcontrol.org) packets.

OSC is an open, transport-independent, message-based protocol developed for communication between computers and other multimedia devices.

See the [Usage](#usage) section below if you are planning to develop applications with **osc++**.

## Installation

### Binary

Debian/Ubuntu/etc:

```shell
$ sudo add-apt-repository ppa:ppa-verse/casparcg
$ sudo apt install libosc++
```

Install the development package, if you are planning to develop applications with **osc++**:
```shell
$ sudo apt install libosc++-dev
```

RaspberryPi:

```shell
sudo add-apt-repository -S deb https://ppa.launchpadcontent.net/ppa-verse/casparcg/ubuntu jammy main
$ sudo apt install libosc++
```

Install the development package, if you are planning to develop applications with **osc++**:
```shell
$ sudo apt install libosc++-dev
```

### From source

Stable version (requires [CMake](https://cmake.org/) >= 3.16):

```shell
$ p=osc v=1.3
$ wget https://github.com/dimitry-ishenko-cpp/${p}/archive/v${v}.tar.gz
$ tar xzf v${v}.tar.gz
$ mkdir ${p}-${v}/build
$ cd ${p}-${v}/build
$ cmake ..
$ make
$ sudo make install
```

Latest master (requires [git](https://git-scm.com/) and [CMake](https://cmake.org/) >= 3.16):

```shell
$ p=osc
$ git clone --recursive https://github.com/dimitry-ishenko-cpp/${p}.git
$ mkdir ${p}/build
$ cd ${p}/build
$ cmake ..
$ make
$ sudo make install
```

## Usage

To use **osc++** in your application simply add:

```c++
#include <osc++.hpp>
```

to your file(s) and link with `-losc++`.

## Description

**osc++** supports all standard OSC data types and most of the non-standard (extended) ones. The following table summarizes which types are supported:

 OSC type | Implemented as
:--------:|:--------------:
[`int32`](https://github.com/dimitry-ishenko-cpp/osc/blob/master/src/types.hpp)   | `std::int32_t`
[`float32`](https://github.com/dimitry-ishenko-cpp/osc/blob/master/src/types.hpp) | `float`
[`string`](https://github.com/dimitry-ishenko-cpp/osc/blob/master/src/types.hpp)  | `std::string`
[`blob`](https://github.com/dimitry-ishenko-cpp/osc/blob/master/src/types.hpp)    | `std::vector<char>`
[`int64`](https://github.com/dimitry-ishenko-cpp/osc/blob/master/src/types.hpp)   | `std::int64_t`
[`time`](https://github.com/dimitry-ishenko-cpp/osc/blob/master/src/types.hpp)    | `clock::time_point`<sup>1</sup>
`double`  | `double`
`char`    | `char`
`true`    | `bool`
`false`   | `bool`
[`nil`](https://github.com/dimitry-ishenko-cpp/osc/blob/master/src/types.hpp)     | `std::nullptr_t`
[`inf`](https://github.com/dimitry-ishenko-cpp/osc/blob/master/src/types.hpp)     | `inf_t`

<sup>1</sup> `using clock = std::chrono::system_clock`.

All supported data types are encapsulated in the [`osc::value`](https://github.com/dimitry-ishenko-cpp/osc/blob/master/src/value.hpp) variant class.

`osc::value` can be implicitly instantiated from any of the supported types, and has `is_...()` and `to_...()` series of functions to query and extract stored value. For example:

```c++
osc::value value{ 42 };
if(value.is_int32()) auto n{ value.to_int32() };
```

```c++
osc::value value{ "The ultimate answer" };
if(value.is_string()) accept(value.to_string());
```

## OSC Packets

OSC data is transmitted in packets. An application transmitting the packets is called _OSC client_, and application receiving the packets is called _OSC server_.

An OSC packet is either an _OSC message_ or an _OSC bundle_.

Within the library packets are represented by the [`osc::packet`](https://github.com/dimitry-ishenko-cpp/osc/blob/master/src/packet.hpp) class, which is a storage container (not entirely unlike `std::vector`) and provides the following functions:

 Function | Description
:--------:|:-----------
[`packet{ }`](https://github.com/dimitry-ishenko-cpp/osc/blob/master/src/packet.hpp)            | Construct empty packet.
[`packet{ size }`](https://github.com/dimitry-ishenko-cpp/osc/blob/master/src/packet.hpp)       | Construct packet of `size` bytes.
[`packet{ data, size }`](https://github.com/dimitry-ishenko-cpp/osc/blob/master/src/packet.hpp) | Construct packet and copy `size` bytes from `data`.
[`packet{ begin, end }`](https://github.com/dimitry-ishenko-cpp/osc/blob/master/src/packet.hpp) | Construct packet and copy data from `[begin, end)`.
[`data()`](https://github.com/dimitry-ishenko-cpp/osc/blob/master/src/packet.hpp)               | Access packet data.
[`size()`](https://github.com/dimitry-ishenko-cpp/osc/blob/master/src/packet.hpp)               | Get packet size.
[`resize(size)`](https://github.com/dimitry-ishenko-cpp/osc/blob/master/src/packet.hpp)         | Resize packet.
[`clear()`](https://github.com/dimitry-ishenko-cpp/osc/blob/master/src/packet.hpp)              | Discard packet data and resize to 0 bytes.

Example of sending a packet using the [asio](https://think-async.com/) library:

```c++
asio::ip::udp::socket socket{ io };
asio::ip::udp::endpoint remote{ ... };
osc::packet packet{ ... };
...
socket.send_to(asio::buffer(packet.data(), packet.size()), remote);
```

Example of receiving a packet:

```c++
asio::ip::udp::socket socket{ io };
...
socket.async_wait(asio::ip::udp::socket::wait_read, [=](const asio::error_code& ec)
{
    osc::packet packet{ static_cast<osc::int32>(socket.available()) };
    asio::ip::udp::endpoint remote;

    socket.receive_from(asio::buffer(packet.data(), packet.size()), remote);
    ...
});
```

As mentioned earlier, a packet is either a message or a bundle. Data stored in the packet can be extracted with the `parse()` function, which returns an instance of [`osc::element`](https://github.com/dimitry-ishenko-cpp/osc/blob/master/src/element.hpp).

`osc::element` is a variant class encapsulating `osc::message` and `osc::bundle`, and has `is_message()`/`is_bundle()` and `to_message()`/`to_bundle()` functions to query and extract stored data. For example:

```c++
auto element{ packet.parse() };
if(element.is_bundle())
{
    auto bundle = element.to_bundle();
    ...
}
else if(element.is_message())
{
    auto message = element.to_message();
    ...
}
```

## OSC Message

OSC message -- represented by the [`osc::message`](https://github.com/dimitry-ishenko-cpp/osc/blob/master/src/message.hpp) class --  consists of an address pattern followed by zero or more arguments, which are instances of `osc::value`.

The address pattern starts with `/` (forward slash) and contains one or more nodes separated by `/`. The pattern can be thought of as a path in a tree-like structure with intermediate nodes called _OSC containers_ and leaf nodes called _OSC methods_.

As such, OSC message can be considered to be a request to execute given method with certain arguments.

`osc::message` provides the following functions:

 Function | Description
:--------:|:-----------
[`message{ address }`](https://github.com/dimitry-ishenko-cpp/osc/blob/master/src/message.hpp) | Construct message with `address`.
[`address()`](https://github.com/dimitry-ishenko-cpp/osc/blob/master/src/message.hpp)          | Get message address.
[`values()`](https://github.com/dimitry-ishenko-cpp/osc/blob/master/src/message.hpp)           | Access message values (returns `std::deque<osc::value>`).
[`value(n)`](https://github.com/dimitry-ishenko-cpp/osc/blob/master/src/message.hpp)           | Access `n`-th value.
[`operator<<(value)`](https://github.com/dimitry-ishenko-cpp/osc/blob/master/src/message.hpp)  | Add `value` to the message.
[`operator>>(T&)`](https://github.com/dimitry-ishenko-cpp/osc/blob/master/src/message.hpp)     | Extract value from the message.
[`to_packet()`](https://github.com/dimitry-ishenko-cpp/osc/blob/master/src/message.hpp)        | Construct packet from the message.

Examples of constructing a message:

```c++
osc::message message{ "/foo/bar/baz" };
message << "So long and thanks for all the fish." << 42;
message << osc::blob{ 100, 'X' };
```

```c++
using namespace osc::literals; // pull in osc::nil and osc::inf
osc::message message{ "/foo/bar/qux" };
message << true << false << nil << inf << osc::clock::now();
```

## OSC Bundle

OSC bundle -- represented by the [`osc::bundle`](https://github.com/dimitry-ishenko-cpp/osc/blob/master/src/bundle.hpp) class -- consists of the `#bundle` keyword, followed by a time tag and zero or more elements.

The time tag indicates when the bundle is to be executed. If the time tag is in the past or the bundle was constructed with [osc::immed](https://github.com/dimitry-ishenko-cpp/osc/blob/master/src/types.hpp) time tag (the default), the bundle is to be executed immediately upon receipt.

Bundle elements are instances of `osc::element` and can themselves be bundles. In other words, bundles can contain other bundles (Inception-style).

`osc::bundle` provides the following functions:

 Function | Description
:--------:|:-----------
[`bundle{ time = immed }`](https://github.com/dimitry-ishenko-cpp/osc/blob/master/src/bundle.hpp) | Construct bundle with tag `time`.
[`time()`](https://github.com/dimitry-ishenko-cpp/osc/blob/master/src/bundle.hpp)                 | Get bundle time.
[`elements()`](https://github.com/dimitry-ishenko-cpp/osc/blob/master/src/bundle.hpp)             | Access bundle elements (returns `std::deque<osc::element>`).
[`element(n)`](https://github.com/dimitry-ishenko-cpp/osc/blob/master/src/bundle.hpp)             | Access `n`-th element.
[`operator<<(element)`](https://github.com/dimitry-ishenko-cpp/osc/blob/master/src/bundle.hpp)    | Add `element` to the bundle.
[`operator>>(message&)`](https://github.com/dimitry-ishenko-cpp/osc/blob/master/src/bundle.hpp)   | Extract message from the bundle.
[`operator>>(bundle&)`](https://github.com/dimitry-ishenko-cpp/osc/blob/master/src/bundle.hpp)    | Extract bundle from the bundle.
[`to_packet()`](https://github.com/dimitry-ishenko-cpp/osc/blob/master/src/bundle.hpp)            | Create packet from the bundle.

Examples of constructing a bundle:

```c++
osc::bundle bundle; // execute immediately
osc::message message{ "/path/to/method" };
message << 1 << 2 << 3.1415926535;
bundle << message;
```

```c++
osc::bundle bundle{ osc::clock::now() + 10min }; // execute 10 min from now
bundle << (osc::message{ "/foo/bar" } << 123 << 987);
bundle << (osc::message{ "/foo/baz" } << "Hello world");
```

Bundle within a bundle example:

```c++
osc::bundle bundle{ osc::clock::now() };
bundle << (osc::message{ "/do/it/now" } << 1 << 2 << 3)         // execute "now"
       << (osc::bundle{ bundle.time() + 1h }
           << (osc::message{ "/do/it/later" } << 4 << 5 << 6)); // execute in 1hr
```

## OSC Client

OSC client -- the one transmitting the packets -- will usually:

 - create a message and/or bundle;
 - construct a packet from it;
 - send it out (by means of another library).

Transmitting example:

```c++
#include <asio.hpp>
#include <osc++.hpp>
using namespace asio::ip::udp;
...
asio::io_context io;
udp::endpoint remote{ ... };
udp::socket socket{ io };

socket.open(udp::v4());

osc::message message{ "/abc/def/ghi" };
message << 123 << 456 << 789;

auto packet = message.to_packet();
socket.send_to(asio::buffer(packet.data(), packet.size()), remote);

osc::bundle bundle;
bundle << (osc::message{ "/a/b/c" } << 1 << 2 << 3)
       << (osc::message{ "/1/2/3" } << 'a' << 'b' << 'c' );

auto packet_2 = bundle.to_packet();
socket.send_to(asio::buffer(packet_2.data(), packet_2.size()), remote);
```

## OSC Server

OSC server -- the one receiving the packets -- usually will:

 - receive a packet;
 - parse it to get an instance of `osc::element`;
 - check if this instance is a message or a bundle;
 - if bundle, recurse into it and check each of its elements;
 - if message, "execute" it.

The `parse()` function may throw one of the following exceptions (derived from `std::invalid_argument`):

| Exception |
|:---------:|
|[`osc::invalid_value`](https://github.com/dimitry-ishenko-cpp/osc/blob/master/src/errors.hpp)   | `std::invalid_argument`
|[`osc::invalid_message`](https://github.com/dimitry-ishenko-cpp/osc/blob/master/src/errors.hpp) | `std::invalid_argument`
|[`osc::invalid_element`](https://github.com/dimitry-ishenko-cpp/osc/blob/master/src/errors.hpp) | `std::invalid_argument`
|[`osc::invalid_bundle`](https://github.com/dimitry-ishenko-cpp/osc/blob/master/src/errors.hpp)  | `std::invalid_argument`
|[`osc::invalid_packet`](https://github.com/dimitry-ishenko-cpp/osc/blob/master/src/errors.hpp)  | `std::invalid_argument`

Receiving example:

```c++
#include <asio.hpp>
#include <osc++.hpp>
using namespace asio::ip::udp;

asio::io_context io;
udp::endpoint local{ ... };
udp::socket socket{ io };

socket.open(udp::v4());
socket.bind(local);

socket.async_wait(udp::socket::wait_read, [=](const asio::error_code& ec)
{
    if(!ec)
    {
        osc::packet packet{ static_cast<osc::int32>(socket.available()) };
        udp::endpoint remote;
        socket.receive_from(asio::buffer(packet.data(), packet.size()), remote);

        try
        {
            auto element{ packet.parse() };
            if(element.is_message())
            {
                auto message{ bundle.to_message() };
                execute(message);
            }
            else if(element.is_bundle())
            {
                auto bundle{ element.to_bundle() };
                recurse_into(bundle);
            }
        }
        catch(std::invalid_argument& e)
        {
            std::cerr << e.what() << std::endl;
        }
        ...
    }
});
```

To help with processing of received packets, `osc::bundle` implements the extraction operator (`>>`) as well as the `elements().are<...>()` function template to check types of its elements.

Let's say we want to implement an OSC server that receives bundles, which contain a message and another bundle with two more messages inside. This can be implemented in the following (boring) way:

```c++
osc::packet packet{ ... };
auto bundle{ packet.parse().to_bundle() };

auto message{ bundle.element(0).to_message() };
auto bundle_2{ bundle.element(1).to_bundle() };

auto message_2{ bundle_2.element(0).to_message() };
auto message_3{ bundle_2.element(1).to_message() };
```

The above example uses the `element()` function and relies on exceptions. We could instead use `operator>>`:

```c++
osc::packet packet{ ... };
auto element{ packet.parse() };

osc::bundle bundle, bundle_2;
osc::message message, message_2, message_3;

element >> bundle;
bundle >> message >> bundle_2;
bundle_2 >> message_2 >> message_3;
```

We can also use `elements().are<...>()` to check bundle signature and avoid exceptions:

```c++
osc::packet packet{ ... };
auto element{ packet.parse() }; // NB: may throw

osc::bundle bundle, bundle_2;
osc::message message, message_2, message_3;

if(element.is_bundle())
{
    element >> bundle;
    if(bundle.elements().are<osc::message, osc::bundle>())
    {
        bundle >> message >> bundle_2;
        if(bundle_2.elements().are<osc::message, osc::message>())
        {
            bundle_2 >> message_2 >> message_3;
            // look ma, no exceptions
            ...
        }
    }
}
```

Likewise, `osc::message` implements `operator>>` and `values().are<...>()` to help check and extract its values:

```c++
osc::message message{ "x/y/z" };
message << "The ultimate answer" << 42 << 2.71828 << osc::clock::now();

if(message.values().are<std::string, int, double, osc::time>())
{
    std::string v1; int v2; double v3; osc::time v4;
    message >> v1 >> v2 >> v3 >> v4;
}
```

## Dispatching

**libosc++** provides _OSC message dispatching_ facility described in the OSC specification. Using this facility an OSC server simply needs to:

 - create an instance of [`osc::address_space`](https://github.com/dimitry-ishenko-cpp/osc/blob/master/src/dispatch.hpp);
 - optionally, supply [`osc::callback_sched`](https://github.com/dimitry-ishenko-cpp/osc/blob/master/src/dispatch.hpp) callback scheduling function;
 - register one or more [`osc::callback`](https://github.com/dimitry-ishenko-cpp/osc/blob/master/src/dispatch.hpp) functions;
 - call [`dispatch()`](https://github.com/dimitry-ishenko-cpp/osc/blob/master/src/dispatch.hpp) for every received packet.

Contrary to the OSC specification though, **libosc++** uses regex for pattern matching within the address space.

Example:

```c++
double x, y, z;

void set_coords(osc::message message) // callback
{
    if(message.values().are<double, double, double>()) message >> x >> y >> z;
}

void set_coord(const osc::message& message) // callback
{
    if(message.values().are<char, double>())
    {
        auto coord = message.value(1).to_double();
        switch(message.value(0).to_char())
        {
        case 'x': x = coord; break;
        case 'y': y = coord; break;
        case 'z': z = coord; break;
        }
    }
}

void print_state(const osc::message& message)
{
    std::cout << "state after " << message.address()
              << ": " << x << " " << y << " " << z << std::endl;
}

...

osc::address_space space;
space.add("/set/coords", &set_coords);
space.add("/set/coord", &set_coord);

#ifndef NDEBUG
space.add("/set/.*", &print_state);
#endif

space.dispatch(osc::message{ "/set/coords" } << 1.2 << 3.4 << 5.6);

space.dispatch(osc::bundle{ }
    << (osc::message{ "/set/coord" } << 'x' << 7.8)
    << (osc::message{ "/set/coord" } << 'y' << 9.0)
);

space.dispatch(osc::message{ "/set/speed" } << 69);
```

Output:

```
state after /set/coords: 1.2 3.4 5.6
state after /set/coord: 7.8 3.4 5.6
state after /set/coord: 7.8 9 5.6
state after /set/speed: 7.8 9 5.6
```

NB: Since the extraction operators (`>>`) modify the message, `set_coords()` above takes `osc::message` by value, which involves copying. On the other hand, `set_coord()` only needs const ref as it uses the `value()` function to access values without extracting them.

`osc::address_space` provides the following functions:

 Function | Description
:--------:|:-----------
[`address_space{ sched = call_immed{ } }`](https://github.com/dimitry-ishenko-cpp/osc/blob/master/src/dispatch.hpp) | Construct empty address space.<sup>2</sup>
[`add(pattern, callback)`](https://github.com/dimitry-ishenko-cpp/osc/blob/master/src/dispatch.hpp)                 | Add `callback` function matching `pattern`.
[`dispatch(element)`](https://github.com/dimitry-ishenko-cpp/osc/blob/master/src/dispatch.hpp)                      | Dispatch received element.

<sup>2</sup> **libosc++** relies on a user-provided `sched` function to schedule callbacks for future execution. The library itself includes default implementation [`osc::call_immed`](https://github.com/dimitry-ishenko-cpp/osc/blob/master/src/dispatch.hpp), which disregards the time tag and executes the callback immediately.

## Authors

* **Dimitry Ishenko** - dimitry (dot) ishenko (at) (gee) mail (dot) com

## License

This project is distributed under the GNU GPL license. See the
[LICENSE.md](LICENSE.md) file for details.
