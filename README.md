# MinVRange

  * [What is this ?](#what-is-this--)
  * [Features and limitations](#features-and-limitations)
  * [Show me some code !](#show-me-some-code--)
  * [TODOs](#todos)

## What is this ?

*Once upon a time*, I had the intention to write a C++ library to perform wavelet transforms (using lifting schemes) but thought in might be funnier to write it in the range-like style of functionnal languages. I started to code a few very minimalistic headers for these ranges which should only operate on an `std::vector` and realized it might be useful on its own. So here it is as a (very) tiny header-only library for using "range"-feeling objects with `std::vector`. 

> N.B: I probably made a lot of mistake while designing the API and you might run into obscure compile error while using it with weird types (if so please let me know).

## Features and limitations

&#8193; &#10133; (quite) easy to use

&#8193; &#10133; very small 

&#8193; &#10134; lots of missing range/indexes (WIP)

&#8193; &#10134; not optimized for speed  

## Show me some code !

```c++
#include <iostream>
#include <string>

#include "mvrg/index/affine.hpp"
#include "mvrg/range/index.hpp"
#include "mvrg/range/map.hpp"
#include "mvrg/vector.hpp"

int main()
{
    mvrg::Vector<std::string> data = {"1", "2", "3", "4", "5", "6", "7"};

    auto input = mvrg::vector::moveToInput(data);

    mvrg::Vector<int> output;

    auto stringToInt = [](const std::string& s) {return std::stoi(s);};

    auto square = [](int i) { return i * i; };

    input >> mvrg::index::affine(2) 
          >> mvrg::range::map(stringToInt)
          >> mvrg::range::map(square) 
          >> output;
 
    for (const auto& e : output)
    {
        std::cout << e << std::endl;
    }

    return 0;
}
```

## TODOs

  - add filter, fold, reverse, interleave..and so much more
  - unit tests ? (Nah with all these variadic temlate checks; if it compiles, I am probably fine isn't it ?)
