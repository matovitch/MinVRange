#ifndef __INDEX_AFFINE_H__
#define __INDEX_AFFINE_H__

#include <cstddef>
#include <memory>

#include "mvrg/index.hpp"

namespace mvrg
{

namespace index
{

class Affine : public Index
{
    Affine() = delete;

public:

    Affine(const std::size_t stride,
           const std::size_t offset = 0) : 
        _stride{stride},
        _offset{offset % stride}
    {}

    std::size_t operator()(const std::size_t state) const
    {
        return _stride * state + _offset;
    }

private:

    std::size_t _stride;
    std::size_t _offset;
};

template <class... Args>
std::shared_ptr<Affine> affine(Args&&... args)
{
    return std::make_shared<Affine>(args...);
}

} // end index namespace
} // end mvrg namespace

#endif // __INDEX_AFFINE_H__