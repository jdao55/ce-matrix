#include "../include/matrix.hpp"
#include <iostream>
#include <algorithm>
#include "../include/operator.hpp"
int main()
{
    constexpr ce::ctmatrix<int, 3, 3> test{ 0, 1, 2, 3, 4, 5, 6, 7, 8 };
    constexpr ce::ctmatrix<int, 3, 3> test2(1);
    constexpr auto i3 = ce::ctmatrix<int, 3,3>::identity();
    constexpr auto res = (test+test2)*i3;
    std::ranges::for_each(res.data, [](int a){std::cout<<a<<" ";});
    return 0;
}
