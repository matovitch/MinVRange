#ifndef __INDEX_IDENTITY_H__
#define __INDEX_IDENTITY_H__

#include <cstddef>
#include <memory>

#include "mvrg/index.hpp"

namespace mvrg
{

namespace index
{

struct Identity : public Index
{
    std::size_t operator()(const std::size_t state) const
    {
        return state;
    }
};

template <class... Args>
std::shared_ptr<Identity> identity(Args&&... args)
{
    return std::make_shared<Identity>(args...);
}

} // end index namespace
} // end mvrg namespace

#endif // __INDEX_IDENTITY_H__