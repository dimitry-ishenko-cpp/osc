////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2020-2025 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "osc++/types.hpp"
#include <deque>

////////////////////////////////////////////////////////////////////////////////
namespace osc
{

class element;

class elements : public std::deque<element>
{
public:
    ////////////////////
    using std::deque<element>::deque;

    template<typename...> bool are() const;

private:
    ////////////////////
    template<std::size_t, typename, typename...>
    constexpr inline bool are_() const;
};

}
