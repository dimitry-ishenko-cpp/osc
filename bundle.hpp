////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2020 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#ifndef OSC_BUNDLE_HPP
#define OSC_BUNDLE_HPP

////////////////////////////////////////////////////////////////////////////////
#include "types.hpp"
#include "elements_0.hpp"
#include "message.hpp"

////////////////////////////////////////////////////////////////////////////////
namespace osc
{

class packet;

////////////////////////////////////////////////////////////////////////////////
class bundle
{
public:
    explicit bundle(osc::time t = immed) : time_{ std::move(t) } { }

    auto const& time() const { return time_; }

    auto const& elements() const { return elements_; }
    auto& elements() { return elements_; }

    auto const& element(std::size_t n) const { return elements_[n]; }
    auto& element(std::size_t n) { return elements_[n]; }

    bundle& operator<<(osc::element);

    bundle& operator>>(message&);
    bundle& operator>>(bundle&);

    int32 space() const; // space requirement
    packet to_packet() const;

    static bool maybe(packet&); // is this packet a bundle?
    static bundle parse(packet&);

private:
    osc::time time_;
    osc::elements elements_;

    void append_to(packet&) const;
    friend class osc::element;
};

////////////////////////////////////////////////////////////////////////////////
}

////////////////////////////////////////////////////////////////////////////////
#endif
