#include "../include/matrix_expr.hpp"
#include <iostream>
#include <algorithm>
#include "../include/operator_expr.hpp"

int main()
{

    constexpr ce::matrix_t<int, 2, 3> A{ 1, 1, 2, 3, 4, 5 };
    constexpr ce::matrix_t<int, 3, 3> B{ 0, 1, 2, 3, 4, 5, 6, 7, 8 };

    constexpr ce::matrix_t<int, 3, 3> C{ 1, 1, 2, 3, 4, 5, 6, 7, 8 };
    ce::matrix_t<int, 2, 3> res = A*C;
    res+=A;
    int i=0;
    std::ranges::for_each(res.data, [&](int a){
                                            std::cout<<a<<" ";
                                            if(i++ % 3 == 2)
                                                std::cout<<'\n';
                                        });
    return 0;
}
