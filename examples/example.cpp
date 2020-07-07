#include "../include/matrix.hpp"
#include <iostream>
#include <algorithm>
#include "../include/operator.hpp"
#include "../include/algorithm.hpp"
int main()
{
    constexpr ce::matrix<int, 3, 3> test{ 0, 1, 2, 3, 4, 5, 6, 7, 8 };
    constexpr ce::matrix<int, 3, 3> test2(1);
    constexpr auto i3 = test * test2 +test - test *5;
    constexpr auto res = ce::add_rows(test, i3);
    int i=0;
    std::ranges::for_each(res.data, [&](int a){
                                        std::cout<<a<<" ";
                                        if(i++ % 3 == 2)
                                            std::cout<<'\n';
                                    });
    return 0;
}
