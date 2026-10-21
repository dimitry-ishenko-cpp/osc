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

////////////////////////////////////////////////////////////////////////////////
namespace osc
{

element packet::parse()
{
    if (bundle::maybe(*this))
        return bundle::parse(*this);

    else if (message::maybe(*this))
        return message::parse(*this);

    else throw invalid_packet{"bad or empty"};
}

void packet::append(const char* data, int32 size)
{
    data_.insert(data_.end(), data, data + size);
}

}
