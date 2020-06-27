#include "matrix.hpp"

#include "operator.hpp"
int main()
{
    constexpr ce::ctmatrix<int, 3, 3> test{ 0, 1, 2, 3, 4, 5, 6, 7, 8 };
    constexpr ce::ctmatrix<int, 3, 3> test2{ 0, 1, 2, 3, 4, 5, 6, 7, 8 };
    constexpr auto res = test+test2;
    constexpr auto res_val = res(0, 1);
    constexpr auto res2 = ce::ctmatrix<int, 3,2>::identity();
    return res_val;
}
