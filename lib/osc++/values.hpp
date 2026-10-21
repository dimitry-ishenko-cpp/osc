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
        return size() == sizeof...(Ts) && are_<0, Ts...>();
    }

private:
    ////////////////////
    template<std::size_t n, typename T, typename... Us>
    constexpr inline bool are_() const
    {
        if constexpr (sizeof...(Us))
            return (*this)[n].is<T>() && are_<n+1, Us...>();
        else return (*this)[n].is<T>();
    }
};

}
