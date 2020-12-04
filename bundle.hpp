////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2020 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#ifndef OSC_BUNDLE_HPP
#define OSC_BUNDLE_HPP

////////////////////////////////////////////////////////////////////////////////
#include "message.hpp"
#include "types.hpp"

#include <variant>
#include <vector>

////////////////////////////////////////////////////////////////////////////////
namespace osc
{

////////////////////////////////////////////////////////////////////////////////
class bundle
{
public:
    class element;

    bundle(time t = clock::now()) : time_(std::move(t)) { }

    auto const& elements() const { return elements_; }
    int32 space() const;

    bundle& operator<<(element);

private:
    time time_;
    std::vector<element> elements_;
};

////////////////////////////////////////////////////////////////////////////////
class bundle::element
{
public:
    element(message m) : cont_(std::move(m)) { }
    element(bundle  b) : cont_(std::move(b)) { }

    bool is_message() const { return std::holds_alternative<message>(cont_); }
    bool is_bundle () const { return std::holds_alternative<bundle >(cont_); }

    auto const& to_message() const { return std::get<message>(cont_); }
    auto const& to_bundle () const { return std::get<bundle >(cont_); }

    int32 space() const;

private:
    std::variant<message, bundle> cont_;
};

////////////////////////////////////////////////////////////////////////////////
inline bundle& bundle::operator<<(element e)
{
    elements_.push_back(std::move(e));
    return *this;
}

////////////////////////////////////////////////////////////////////////////////
}

////////////////////////////////////////////////////////////////////////////////
#endif
