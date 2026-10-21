////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2020-2025 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "osc++/types.hpp"

#include <string_view>
#include <vector>

////////////////////////////////////////////////////////////////////////////////
namespace osc
{

class element;
class message;

class packet
{
public:
    ////////////////////
    packet() = default;
    explicit packet(int32 size) : data_(size) { }
    packet(const char* data, int32 size) : packet{data, data + size} { }
    packet(const char* begin, const char* end) : data_{begin, end} { }

    ////////////////////
    auto data() const { return data_.data(); }
    auto data() { return data_.data(); }

    int32 size() const { return data_.size(); }
    void resize(int32 size) { data_.resize(size); }
    void clear() { data_.clear(); }

    element parse() const;

private:
    ////////////////////
    std::vector<char> data_;
    void append(const char*, int32);

    static std::string_view take(std::string_view&, int32);

    friend class bundle;
    friend class element;
    friend class message;
    friend class value;
};

}
