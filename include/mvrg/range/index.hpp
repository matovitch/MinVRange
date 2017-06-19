#ifndef __RANGE_INDEX_H__
#define __RANGE_INDEX_H__

#include <cstddef>
#include <memory>

#include "mvrg/vector.hpp"
#include "mvrg/index.hpp"
#include "mvrg/range.hpp"

namespace mvrg
{

namespace range
{

template <typename T>
class Index;

using namespace index;

template <typename T>
class Index : public Range<T>
{
    Index() = delete;

public:

    Index(const vector::SPtr<T>& input, 
          const index ::SPtr& index) :
        _input{input},
        _index{index}
    {}

    const T& operator()(const std::size_t state) const
    {
        return (*_input)[(*_index)(state)];
    }

    bool isValid(const std::size_t state) const
    {
        return (*_index)(state) < _input->size() && 
               (*_index)(state) >= 0;
    }

    class View : public range::View<T>
    {
        View() = delete;

    public:

        View(const Index<T>* const index) :
            _index(index),
            _state(0)
        {}

        bool isValid() const
        {
            return _index->isValid(_state);
        }

        void forward   () { _state++; }
        void backward  () { _state--; }

        const T& operator()() const
        {
            return (*_index)(_state);
        }

    private:

        const Index<T>* const _index;
        std::size_t           _state;
    };

    View& view()
    {
        _views.push_back(View{this});

        return _views.back();
    }

private:

    const vector::SPtr<T> _input;
    const index ::SPtr    _index;

    std::vector<View> _views;
};

} // end range namespace

} // end mvrg namespace

using namespace mvrg;

template <typename T>
auto operator >> (const vector::SPtr<T>& input, 
                  const index ::SPtr   & index)
{
    return std::make_shared<range::Index<T>>(input, index);
}

#endif // __RANGE_H__