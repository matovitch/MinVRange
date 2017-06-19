#ifndef __INDEX_COMPOSED_H__
#define __INDEX_COMPOSED_H__

#include <cstddef>
#include <memory>

#include "mvrg/index.hpp"

namespace mvrg
{

namespace index
{

class Composed;

namespace composed
{
    typedef std::shared_ptr<Composed> SPtr;
}

class Composed : public Index
{

    Composed() = delete;

public:

    Composed(const index   ::SPtr& index,
             const composed::SPtr& composed = composed::SPtr{}) :
        _composed(composed),
        _index   (index   )
    {}

    std::size_t operator()(const std::size_t state) const
    {
        return _composed ? (*_composed)((*_index)(state)) 
                         :              (*_index)(state);
    }

private:

    const composed::SPtr _composed;
    const index::SPtr    _index;
};

} // end index namespace
} // end mvrg namespace

composed::SPtr operator % (const index::SPtr& lIndex, 
                           const index::SPtr& rIndex)
{
    return std::make_shared<Composed>(rIndex, 
                                      std::make_shared<Composed>(lIndex));
}

composed::SPtr operator % (const composed::SPtr& composed, 
                           const index   ::SPtr& index)
{
    return std::make_shared<Composed>(index, composed);
}

#endif // __INDEX_COMPOSED_H__