////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2020 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#include <stdexcept>
#include <string>

////////////////////////////////////////////////////////////////////////////////
namespace osc
{

////////////////////////////////////////////////////////////////////////////////
class invalid_value : public std::invalid_argument
{
public:
    invalid_value() : std::invalid_argument("Invalid value") { }
    explicit invalid_value(const std::string& why) : std::invalid_argument("Invalid value - " + why) { }
};

////////////////////////////////////////////////////////////////////////////////
class invalid_message : public std::invalid_argument
{
public:
    invalid_message() : std::invalid_argument("Invalid message") { }
    explicit invalid_message(const std::string& why) : std::invalid_argument("Invalid message - " + why) { }
};

////////////////////////////////////////////////////////////////////////////////
class invalid_element : public std::invalid_argument
{
public:
    invalid_element() : std::invalid_argument("Invalid element") { }
    explicit invalid_element(const std::string& why) : std::invalid_argument("Invalid element - " + why) { }
};

////////////////////////////////////////////////////////////////////////////////
class invalid_bundle : public std::invalid_argument
{
public:
    invalid_bundle() : std::invalid_argument("Invalid bundle") { }
    explicit invalid_bundle(const std::string& why) : std::invalid_argument("Invalid bundle - " + why) { }
};

////////////////////////////////////////////////////////////////////////////////
class invalid_packet : public std::invalid_argument
{
public:
    invalid_packet() : std::invalid_argument("Invalid packet") { }
    explicit invalid_packet(const std::string& why) : std::invalid_argument("Invalid packet - " + why) { }
};

////////////////////////////////////////////////////////////////////////////////
}
