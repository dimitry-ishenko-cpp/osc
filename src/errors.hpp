////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2020 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#ifndef OSC_ERRORS_HPP
#define OSC_ERRORS_HPP

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
    explicit invalid_value(const std::string& why) :
        std::invalid_argument{ "Invalid value - " + why }
    { }
    invalid_value() : std::invalid_argument{ "Invalid value" } { }
};

////////////////////////////////////////////////////////////////////////////////
class invalid_message : public std::invalid_argument
{
public:
    explicit invalid_message(const std::string& why) :
        std::invalid_argument{ "Invalid message - " + why }
    { }
    invalid_message() : std::invalid_argument{ "Invalid message" } { }
};

////////////////////////////////////////////////////////////////////////////////
class invalid_element : public std::invalid_argument
{
public:
    explicit invalid_element(const std::string& why) :
        std::invalid_argument{ "Invalid element - " + why }
    { }
    invalid_element() : std::invalid_argument{ "Invalid element" } { }
};

////////////////////////////////////////////////////////////////////////////////
class invalid_bundle : public std::invalid_argument
{
public:
    explicit invalid_bundle(const std::string& why) :
        std::invalid_argument{ "Invalid bundle - " + why }
    { }
    invalid_bundle() : std::invalid_argument{ "Invalid bundle" } { }
};

////////////////////////////////////////////////////////////////////////////////
class invalid_packet : public std::invalid_argument
{
public:
    explicit invalid_packet(const std::string& why) :
        std::invalid_argument{ "Invalid packet - " + why }
    { }
    invalid_packet() : std::invalid_argument{ "Invalid packet" } { }
};

////////////////////////////////////////////////////////////////////////////////
}

////////////////////////////////////////////////////////////////////////////////
#endif
