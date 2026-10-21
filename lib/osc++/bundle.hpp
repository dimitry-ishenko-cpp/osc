////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2020-2025 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "osc++/types.hpp"
#include "osc++/elements_0.hpp"
#include "osc++/message.hpp"

#include <string_view>

////////////////////////////////////////////////////////////////////////////////
namespace osc
{

class packet;

class bundle
{
public:
    ////////////////////
    explicit bundle(osc::time t = immed) : time_{std::move(t)} { }

    ////////////////////
    auto& time() const { return time_; }

    auto& elements() const { return elements_; }
    auto& elements() { return elements_; }

    auto& element(std::size_t n) const { return elements_.at(n); }
    auto& element(std::size_t n) { return elements_.at(n); }

    bundle& operator<<(osc::element);

    bundle& operator>>(message&);
    bundle& operator>>(bundle&);

    int32 space() const; // space requirement
    packet to_packet() const;

    ////////////////////
    static bool maybe(std::string_view); // is this packet a bundle?
    static bundle parse(std::string_view&);

private:
    ////////////////////
    osc::time time_;
    osc::elements elements_;

    void append_to(packet&) const;
    friend class osc::element;
};

}
