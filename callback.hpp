////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2020 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#ifndef OSC_CALLBACK_HPP
#define OSC_CALLBACK_HPP

////////////////////////////////////////////////////////////////////////////////
#include "values.hpp"

#include <functional>
#include <type_traits>
#include <utility>

////////////////////////////////////////////////////////////////////////////////
namespace osc
{

struct callback
{
    template<typename Callable>
    callback(Callable fn) : call_(adaptor<Callable>::to_call( std::move(fn) )) { }

    void operator()(const values& vv) const { call_(vv); }

private:
    // the call function
    using call = std::function<void (const values&)>;
    call call_;

    // callable wrapped inside std::function
    template<typename... Args>
    using callable = std::function<void (Args...)>;

    // turn callable into call
    template<typename... Args, std::size_t... Is>
    static call to_call_(callable<Args...> fn, std::index_sequence<Is...>)
    {
        return [fn_ = std::move(fn)](const values& vv) {
            if(vv.are<Args...>()) fn_(vv[Is].to<Args>()...);
        };
    }

    // adaptor class template
    template<typename C, typename = void>
    struct adaptor { };

    template<typename... Args>
    struct adaptor<callable<Args...>>
    {
        static auto to_call(callable<Args...> fn)
        {
            constexpr auto N = sizeof...(Args);
            return to_call_(std::move(fn), std::make_index_sequence<N>());
        }
    };

    template<typename... Args>
    struct adaptor<void (*)(Args...)> :
        public adaptor<callable<Args...>>
    { };

    template<typename C, typename... Args>
    struct adaptor<void (C::*)(Args...)> : 
        public adaptor<callable<Args...>> 
    { };

    template<typename C, typename... Args>
    struct adaptor<void (C::*)(Args...) const> :
        public adaptor<void (C::*)(Args...)>
    { };

    template<typename C>
    struct adaptor<C, std::void_t<decltype( &C::operator() )>> :
        public adaptor<decltype( &C::operator() )>
    { };
};

////////////////////////////////////////////////////////////////////////////////
}

////////////////////////////////////////////////////////////////////////////////
#endif

