
#include <iostream>
#include <algorithm>
#include <cematrix.hpp>


int main()
{
    using namespace ce::crtp;
    constexpr matrix_t<float, 3, 3> A{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    constexpr matrix_t<float, 3, 3> B{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    constexpr matrix_t<float, 3, 3> C{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    constexpr matrix_t<float, 3, 3> D = A + B + C;
    constexpr matrix_t<float, 3, 3> E = A * B + C;
}
