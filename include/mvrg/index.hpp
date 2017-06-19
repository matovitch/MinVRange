#ifndef __INDEX_H__
#define __INDEX_H__

#include <cstddef>
#include <memory>

namespace mvrg
{

struct Index
{
    virtual std::size_t operator()(const std::size_t state) const = 0; 
};

namespace index
{
    typedef std::shared_ptr<Index> SPtr;
}

} // end mvrg namespace

#endif // __INDEX_H__