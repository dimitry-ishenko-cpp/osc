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

void dispatch_(const address_space& space, const element& e, time t, const call_sched& sched)
{
    if(e.is_bundle())
    {
        auto b = e.to_bundle();
        for(auto const& e : b.elements()) dispatch_(space, e, b.time(), sched);
    }
    else if(e.is_message())
    {
        auto m = e.to_message();

        for(auto const& e : space)
            if(e.matches(m.address()))
            {
                auto fn = e.bound_callable( m.values() );
                sched(t, fn);
            }
    }
}

}

////////////////////////////////////////////////////////////////////////////////
void dispatch(const address_space& space, const element& e, const call_sched& sched)
{
    dispatch_(space, e, immed, sched);
}

////////////////////////////////////////////////////////////////////////////////
}