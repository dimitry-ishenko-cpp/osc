////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2020 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#ifndef OSC_DISPATCH_HPP
#define OSC_DISPATCH_HPP

////////////////////////////////////////////////////////////////////////////////
#include "element.hpp"
#include "message.hpp"
#include "types.hpp" // time

#include <functional>
#include <regex>
#include <vector>

////////////////////////////////////////////////////////////////////////////////
namespace osc
{

////////////////////////////////////////////////////////////////////////////////
using callback = std::function<void (const message&)>;
using bound_callback = std::function<void ()>;

// address space entry
struct entry
{
    // NB: the pattern is a regex rather than an OSC globbing rule
    entry(const string& pattern, callback fn) :
        re_(pattern), cb_(std::move(fn))
    { }

    bool matches(const message& m) const { return std::regex_match(m.address(), re_); }

    void call(const message& m) const { cb_(m); }
    auto bind(const message& m) const { return std::bind(cb_, m); }

private:
    std::regex re_;
    callback cb_;
};

////////////////////////////////////////////////////////////////////////////////
using address_space = std::vector<entry>;

// callback scheduler
using call_sched = std::function<void (time, const bound_callback&)>;

// default callback scheduler (ignores time)
struct default_sched
{
    void operator()(time, const bound_callback& cb) const { cb(); }
};

void dispatch(const address_space&, const element&, const call_sched& = default_sched());

////////////////////////////////////////////////////////////////////////////////
}

////////////////////////////////////////////////////////////////////////////////
#endif
