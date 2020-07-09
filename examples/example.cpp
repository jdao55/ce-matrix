#include "../include/matrix_expr.hpp"
#include <iostream>
#include <algorithm>
#include "../include/operator_expr.hpp"

int main()
{

    // test_nc+=test;
    // constexpr ce::matrix<int, 3, 3> test2(1);
    // constexpr auto i3 = test * test2 +test - test *5;
    // constexpr auto res = ce::add_rows(test, i3);
    // int i=0;
    // std::ranges::for_each(res.data, [&](int a){
    //                                     std::cout<<a<<" ";
    //                                     if(i++ % 3 == 2)
    //                                         std::cout<<'\n';
    //                                 });
    // std::ranges::for_each(test_nc.data, [&](int a){
    //                                     std::cout<<a<<" ";
    //                                     if(i++ % 3 == 2)
    //                                         std::cout<<'\n';
    //                                 });
    // auto sum_mat = ce::sum(test);
    // std::cout<<"sum: "<<sum_mat<<"\n";
    // auto prod_mat = ce::product(test);
    // std::cout<<"prod: "<<prod_mat<<"\n";
    constexpr ce::matrix_t<int, 3, 3> A{ 1, 1, 2, 3, 4, 5, 6, 7, 8 };
    constexpr ce::matrix_t<int, 3, 3> B{ 0, 1, 2, 3, 4, 5, 6, 7, 8 };

     constexpr ce::matrix_t<int, 3, 3> C{ 0, 1, 2, 3, 4, 5, 6, 7, 8 };
    ce::matrix_t<int, 3, 3> res = A+B+C;
    int i=0;
    std::ranges::for_each(res.data, [&](int a){
                                            std::cout<<a<<" ";
                                            if(i++ % 3 == 2)
                                                std::cout<<'\n';
                                        });
    return 0;
}
