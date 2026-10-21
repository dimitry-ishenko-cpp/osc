////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2020-2025 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "osc++/types.hpp"
#include "osc++/value.hpp"

#include <deque>

////////////////////////////////////////////////////////////////////////////////
namespace osc
{

class values : public std::deque<value>
{
public:
    ////////////////////
    using std::deque<value>::deque;

    template<typename... Ts>
    bool are() const
    {
        if(size() != sizeof...(Ts)) return false;

        [[maybe_unused]] std::size_t n = 0;
        return (... && (*this)[n++].is<Ts>());
    }
};

}
