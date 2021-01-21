////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2020 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#ifndef OSC_ELEMENT_HPP
#define OSC_ELEMENT_HPP

////////////////////////////////////////////////////////////////////////////////
#include "bundle.hpp"
#include "message.hpp"
#include "types.hpp"

#include <variant>

////////////////////////////////////////////////////////////////////////////////
namespace osc
{

class packet;

////////////////////////////////////////////////////////////////////////////////
// An element of a bundle, which is either a bundle itself or a message.
class element
{
public:
    element(message m) : element_{ std::move(m) } { }
    element(bundle  b) : element_{ std::move(b) } { }

    template<typename T>
    bool is() const { return std::holds_alternative<T>(element_); }

    bool is_message() const { return is<message>(); }
    bool is_bundle () const { return is<bundle >(); }

    template<typename T>
    auto const& to() const { return std::get<T>(element_); }

    auto const& to_message() const { return to<message>(); }
    auto const& to_bundle () const { return to<bundle >(); }

    int32 space() const; // space requirement

    static bool maybe(packet&); // is this packet an element?
    static element parse(packet&);

private:
    std::variant<message, bundle> element_;

    void append_to(packet&) const; // append element to packet
    friend class bundle;
};

////////////////////////////////////////////////////////////////////////////////
}

////////////////////////////////////////////////////////////////////////////////
#endif
