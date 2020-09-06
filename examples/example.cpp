
#include <iostream>
#include <algorithm>
#include <cematrix.hpp>


int main()
{
    constexpr ce::matrix_t<float, 3, 3> A{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    constexpr ce::matrix_t<float, 3, 3> B{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    constexpr ce::matrix_t<float, 3, 3> C{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    constexpr ce::matrix_t<float, 3, 3> D = A + B + C;
    constexpr ce::matrix_t<float, 3, 3> E = A * B + C;
}
