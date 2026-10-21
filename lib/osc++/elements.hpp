////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2020-2025 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "osc++/element.hpp"
#include "osc++/elements_0.hpp"

////////////////////////////////////////////////////////////////////////////////
namespace osc
{

template<typename... Ts>
bool elements::are() const
{
    if(size() != sizeof...(Ts)) return false;

    [[maybe_unused]] std::size_t n = 0;
    return (... && (*this)[n++].is<Ts>());
}

}
