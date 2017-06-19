#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <memory>
#include <vector>

namespace mvrg
{

template <typename T>
using Vector = std::vector<T>;

namespace vector
{
    
    template <typename T>
    using SPtr = std::shared_ptr<Vector<T>>;

    template <typename T>
    vector::SPtr<T> moveToInput(Vector<T>& vector)
    {
        return std::make_shared<Vector<T>>(std::move(vector));
    }
} // end vector namespace

} // end mvrg namespace

#endif // __VECTOR_H__