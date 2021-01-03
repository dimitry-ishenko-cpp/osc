////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2020 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#ifndef OSC_DISPATCH_HPP
#define OSC_DISPATCH_HPP

////////////////////////////////////////////////////////////////////////////////
#include "callback.hpp"
#include "element.hpp"
#include "message.hpp"
#include "types.hpp"
#include "values.hpp"

#include <functional>
#include <regex>
#include <vector>

////////////////////////////////////////////////////////////////////////////////
namespace osc
{

////////////////////////////////////////////////////////////////////////////////
using bound_callable = std::function<void ()>;

// address space entry
// NB: the pattern is a regex rather than an OSC globbing rule
struct entry
{
    template<typename Callable>
    entry(const string& pattern, Callable fn) :
        re_(pattern), cb_(callback( std::move(fn) ))
    { }

    bool matches(const string& address) const { return std::regex_match(address, re_); }
    osc::bound_callable bound_callable(const values& vv) const { return std::bind(cb_, vv); }

private:
    std::regex re_;
    callback cb_;
};

////////////////////////////////////////////////////////////////////////////////
using address_space = std::vector<entry>;

// callback scheduler
using call_sched = std::function<void (time, const bound_callable&)>;

// default callback scheduler (ignores time)
struct default_sched
{
    void operator()(time, const bound_callable& fn) const { fn(); }
};

void dispatch(const address_space&, const element&, const call_sched& = default_sched());

////////////////////////////////////////////////////////////////////////////////
}

////////////////////////////////////////////////////////////////////////////////
#endif
