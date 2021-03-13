////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2020 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#include "dispatch.hpp"

////////////////////////////////////////////////////////////////////////////////
namespace osc
{

////////////////////////////////////////////////////////////////////////////////
void address_space::add(const std::string& pattern, callback cb)
{
    entries_.push_back(entry{ std::regex{ pattern }, std::move(cb) });
}

////////////////////////////////////////////////////////////////////////////////
void address_space::dispatch(const element& e, time t)
{
    if(e.is_bundle())
    {
        auto b = e.to_bundle();
        for(auto const& el : b.elements()) dispatch(el, b.time());
    }
    else if(e.is_message())
    {
        auto m = e.to_message();
        for(auto const& en : entries_)
        {
            auto match = std::regex_match(m.address(), en.re);
            if(match) sched_(t, std::bind(en.cb, m));
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
}
