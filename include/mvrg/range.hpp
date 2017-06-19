#ifndef __RANGE_H__
#define __RANGE_H__

#include <memory>

#include "mvrg/vector.hpp"

namespace mvrg
{

namespace range
{
    template <typename T>
    struct View
    {
        virtual const T& operator()() const = 0;

        virtual bool isValid() const = 0;

        virtual void  forward() = 0;
        virtual void backward() = 0;
    };

    template <template <typename...> typename RANGE, typename... Args>
    typename RANGE<Args...>::View& view(const std::shared_ptr<RANGE<Args...>>& range)
    {
        return range->view();
    }
} // end range namespace

template <typename T>
struct Range 
{
    typedef T type;

    virtual range::View<T>& view() = 0;
};

template <template <typename...> typename RANGE, typename... Args>
void operator >> (const std::shared_ptr<RANGE<Args...>>& range, 
                  Vector<typename RANGE<Args...>::type>& output)
{
    auto view = range::view(range);

    while (view.isValid())
    {
        output.push_back(view());
        view.forward();
    }
}

} // end mvrg namespace

#endif // __RANGE_H__