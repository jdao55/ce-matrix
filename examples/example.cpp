
#include <iostream>
#include <algorithm>
#include <cematrix.hpp>


int main()
{
    using namespace ce::vari;
    constexpr matrix_t<float, 3, 3> A{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    constexpr matrix_t<float, 3, 3> B{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    constexpr matrix_t<float, 3, 3> C{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    constexpr matrix_t<float, 3, 3> D = A + B + C;
    constexpr matrix_t<float, 3, 3> E = A * B + C;

    constexpr vector_t<int, 3> v1{ 1, 2, 3 };
    constexpr vector_t<int, 3> v2{ 2, 3, 4 };
    constexpr auto v3 = ce::vari::dot_product(v1, v2);
    static_assert(v3 == 20, "error wrong dot product value");
}
