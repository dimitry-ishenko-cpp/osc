////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2020-2025 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#include "osc++/bundle.hpp"
#include "osc++/element.hpp"
#include "osc++/errors.hpp"
#include "osc++/message.hpp"
#include "osc++/packet.hpp"

#include <iterator> // std::ssize

////////////////////////////////////////////////////////////////////////////////
namespace osc
{

element packet::parse() const
{
    std::string_view p{data_};
    return element::parse(p);
}

void packet::append(const char* data, int32 size)
{
    data_.insert(data_.end(), data, data + size);
}

std::string_view packet::take(std::string_view& v, int32 n)
{
    if (n < 0 || n > std::ssize(v)) throw invalid_packet{"bad size"};

    auto head = v.substr(0, n);
    v.remove_prefix(n);

    return head;
}

}
