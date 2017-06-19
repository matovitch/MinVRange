#ifndef __RANGE_MAP_H__
#define __RANGE_MAP_H__

#include <memory>

#include "mvrg/index/identity.hpp"
#include "mvrg/range.hpp"
#include "mvrg/utils.hpp"

namespace mvrg
{

namespace range
{

template <typename RANGE_T, typename U>
class Map : public Range<U>
{

    typedef typename RANGE_T::type T;

public:

    Map(const std::shared_ptr<RANGE_T>& range, 
        const std::function<U(const T&)>& funct) :
        _range{range},
        _funct{funct}
    {}

    class View : public range::View<U>
    {
        View() = delete;

    public:

        View(const Map<RANGE_T, U>* const map) :
            _map{map},
            _view{range::view(map->_range)}
        {}

        bool isValid() const
        {
            return _view.isValid();
        }

        void forward   () { _view. forward(); }
        void backward  () { _view.backward(); }

        const U& operator()() const
        {
            _state = _map->_funct(_view());
            return _state;
        }

    private:

        const Map<RANGE_T, U>* const _map;
        typename RANGE_T::View&      _view;
        mutable U                    _state;
    };

    View& view()
    {
        _views.push_back(View{this});

        return _views.back();
    }

private:

    const std::shared_ptr<RANGE_T> _range;
    std::function<U(const T&)>      _funct;

    std::vector<View>    _views;
};

template <typename F>
utils::Wrap<F> map(const F& f)
{
    return utils::Wrap<F>{f};
}

} // end range namespace

} // end mvrg namespace

using namespace mvrg;

template <typename F, template <typename...> typename RANGE, typename... Args>
auto operator >> (const std::shared_ptr<RANGE<Args...>>& range, 
                  const utils::Wrap<F>& map)
{
    typedef typename RANGE<Args...>::type T;
    typedef typename std::result_of<F(T)>::type U;

    return std::make_shared<range::Map<RANGE<Args...>, U>>(range, map());
}

template <typename T, typename F>
auto operator >> (const vector::SPtr<T>& input, 
                  const utils::Wrap<F>& map)
{
    return input >> index::identity() >> map;
}

#endif // __RANGE_MAP_H__