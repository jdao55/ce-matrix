#include "vari_expr.hpp"
#include "matrix.hpp"
#include <iostream>
int main()
{
    using namespace ce;
    constexpr vari::matrix_t<3, 3> A{ 1, 2, 3, 4, 5, 6, 7, 9, 0 };
    constexpr vari::matrix_t<3, 3> B{ 1, 1, 0, 0, 1, 0, 0, 0, 1 };
    constexpr vari::matrix_t<3, 3> I{ 1, 0, 0, 0, 1, 0, 0, 0, 1 };
    constexpr vari::matrix_t<3, 3> C = A * B * 2 + I;

    std::cout << C[0] << " " << C[1] << " " << C[2] << std::endl;
    std::cout << C[3] << " " << C[4] << " " << C[5] << std::endl;
    std::cout << C[6] << " " << C[7] << " " << C[8] << std::endl;
}
