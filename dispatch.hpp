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

#include <cstddef> // std::size_t
#include <functional>
#include <regex>
#include <vector>

////////////////////////////////////////////////////////////////////////////////
namespace osc
{

////////////////////////////////////////////////////////////////////////////////
using callback = std::function<void (const message&)>;
using bound_callback = std::function<void ()>;

// callback scheduler
using callback_sched = std::function<void (time, const bound_callback&)>;

// immediate callback scheduler (ignores time)
struct call_immed
{
    void operator()(time, const bound_callback& cb) const { cb(); }
};

////////////////////////////////////////////////////////////////////////////////
class address_space
{
public:
    explicit address_space(callback_sched sched = call_immed{ }) :
        sched_{ std::move(sched) }
    { }

    // NB: the pattern is a regex, which differs from the OSC spec
    void add(const std::string& pattern, callback);

    std::size_t dispatch(const element& e) { return dispatch(0, e, immed); }

private:
    callback_sched sched_;
    struct entry
    {
        std::regex re;
        callback cb;
    };
    std::vector<entry> entries_;

    std::size_t dispatch(std::size_t n, const element&, time);
};

////////////////////////////////////////////////////////////////////////////////
}

////////////////////////////////////////////////////////////////////////////////
#endif
