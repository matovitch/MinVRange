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