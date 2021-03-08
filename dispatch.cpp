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
namespace
{

void dispatch_(const address_space& space, const element& e, time t, const callback_sched& sched)
{
    if(e.is_bundle())
    {
        auto b = e.to_bundle();
        for(auto const& el : b.elements()) dispatch_(space, el, b.time(), sched);
    }
    else if(e.is_message())
    {
        auto m = e.to_message();
        for(auto const& en : space) if(en.matches(m)) sched(t, en.bind(m));
    }
}

}

////////////////////////////////////////////////////////////////////////////////
void dispatch(const address_space& space, const element& e, const callback_sched& sched)
{
    dispatch_(space, e, immed, sched);
}

////////////////////////////////////////////////////////////////////////////////
}
