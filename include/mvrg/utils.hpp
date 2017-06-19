#ifndef __UTILS_H__
#define __UTILS_H__

namespace mvrg
{

namespace utils
{

template <typename T>
struct Wrap
{
    Wrap(const T& t) : _t{t} {}

    const T& operator()() const { return _t; }

    const T& _t;
};

} // end utils namespace

} // end mvrg namespace

#endif // __UTILS_H__