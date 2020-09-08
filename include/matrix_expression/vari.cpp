#include "vari_expr.hpp"
#include <iostream>
int main()
{
    constexpr vari::mat<3, 3> A{ 1, 2, 3, 4, 5, 6, 7, 9, 0 };
    constexpr vari::mat<3, 3> B{ 1, 0, 0, 0, 1, 0, 0, 0, 1 };
    constexpr vari::mat<3, 3> C = A + B;
    std::cout << C[0] << " " << C[1] << " " << C[2] << std::endl;
}
