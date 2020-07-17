#include "nanobench.h"
#include <random>
#include <atomic>

#include "../include/cematrix.hpp"
#include "../include/old_stuff/matrix.hpp"
#include "../include/old_stuff/operator.hpp"

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
