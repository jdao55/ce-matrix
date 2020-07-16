#include "../include/matrix_expr.hpp"
#include <iostream>
#include <algorithm>
#include "../include/operator_expr.hpp"
#include "../include/matrix.hpp"
#include <iostream>
#include <algorithm>
#include "../include/operator.hpp"

// int main()
// {

//     constexpr ce::matrix_t<int, 2, 3> A{ 1, 1, 2, 3, 4, 5 };
//     constexpr ce::matrix_t<int, 3, 3> B{ 3, 1, -2, 4, 9, 0, 0, 7, 8 };

//     constexpr ce::matrix_t<int, 3, 3> C{ 1, 1, 2, 3, 4, 5, 6, 7, 8 };
//     ce::matrix_t<int, 2, 3> res = A*B - A*C;
//     int i=0;
//     std::ranges::for_each(res.data, [&](int a){
//                                             std::cout<<a<<" ";
//                                             if(i++ % 3 == 2)
//                                                 std::cout<<'\n';
//                                         });
//     return 0;
// }

#include "nanobench.h"
#include <random>
#include <atomic>

using fmat64_t = ce::matrix_t<float, 64, 64>;
using fmat64 = ce::matrix<float, 64, 64>;

std::random_device rd;
std::mt19937 e2(rd());
std::uniform_real_distribution<float> dist(-255,255);

fmat64_t randmat64_t ()
{
    std::array<float, 64*64> ret{};
    for (auto & element: ret)
    {
        element = dist(e2);
    }
    fmat64_t ret_mat{};
    ret_mat.data = ret;
    return ret_mat;
}

fmat64 randmat64 ()
{
    std::array<float, 64*64> ret{};
    for (auto & element: ret)
    {
        element = dist(e2);
    }
    fmat64 ret_mat{};
    ret_mat.data = ret;
    return ret_mat;
}

void benchnormal(ankerl::nanobench::Bench* bench)
{
    auto a = randmat64();
    auto b = randmat64();
    auto c = randmat64();
    bench->run("normal", [&](){
                           auto d = a*b - a*c;
                           ankerl::nanobench::doNotOptimizeAway(d);
                       });

}

void bench_expr(ankerl::nanobench::Bench* bench){
    auto a = randmat64_t();
    auto b = randmat64_t();
    auto c = randmat64_t();
    bench->run("expression tempaltes", [&](){
                           auto d = a*b - a*c;
                           ankerl::nanobench::doNotOptimizeAway(d);
                       });
}


int main() {

    ankerl::nanobench::Bench b;
    b.title("Expression templates benchmark")
        .unit("operations")
        .warmup(100)
        .relative(true);
    b.performanceCounters(true);
    bench_expr(&b);
    benchnormal(&b);

}
