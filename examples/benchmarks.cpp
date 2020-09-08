#include "nanobench.h"
#include <Eigen/Dense>
#include <random>
#include <iostream>
#include <atomic>
#include <memory>
#include "../include/cematrix.hpp"
#include "../include/old_stuff/matrix.hpp"
#include "../include/old_stuff/operator.hpp"

constexpr auto N = 128;
using sc_t = int;
using fmatNN_t = ce::matrix_t<sc_t, N, N>;
using fmatNN = ce::matrix<sc_t, N, N>;

std::random_device rd;
ankerl::nanobench::Rng e2(rd());
std::uniform_int_distribution<sc_t> dist(-5000, 5000);

fmatNN rand_ce_mat()
{
    std::array<sc_t, N * N> ret{};
    for (auto &element : ret)
    {
        element = dist(e2);
    }
    fmatNN ret_mat{};
    ret_mat.data = ret;
    return ret_mat;
}

fmatNN_t rand_ce_expr_mat()
{
    std::array<sc_t, N * N> ret{};
    for (auto &element : ret)
    {
        element = dist(e2);
    }
    fmatNN_t ret_mat{};
    ret_mat.data = ret;
    return ret_mat;
}

void benchnormal(ankerl::nanobench::Bench *bench)
{
    const fmatNN a = rand_ce_mat();
    const fmatNN b = rand_ce_mat();
    const fmatNN c = rand_ce_mat();

    bench->run("normal", [&]() {
        fmatNN res = (a * b + a * c);
        ankerl::nanobench::doNotOptimizeAway(res);
    });
}

void bench_expr(ankerl::nanobench::Bench *bench)
{
    const fmatNN_t a = rand_ce_expr_mat();
    const fmatNN_t b = rand_ce_expr_mat();
    const fmatNN_t c = rand_ce_expr_mat();

    bench->run("expr", [&]() {
        fmatNN_t res = (a * b + a * c);
        ankerl::nanobench::doNotOptimizeAway(res);
    });
}
void bench_Eigen(ankerl::nanobench::Bench *bench)
{
    const Eigen::Matrix<sc_t, N, N> a = Eigen::Matrix<sc_t, N, N>::Random();
    const Eigen::Matrix<sc_t, N, N> b = Eigen::Matrix<sc_t, N, N>::Random();
    const Eigen::Matrix<sc_t, N, N> c = Eigen::Matrix<sc_t, N, N>::Random();

    bench->run("Eigen", [&]() {
        Eigen::Matrix<sc_t, N, N> res = (a * b + a * c);
        ankerl::nanobench::doNotOptimizeAway(res);
    });
}

int main()
{

    ankerl::nanobench::Bench b;
    b.title("Expression templates benchmark").unit("expr").warmup(500).relative(true);
    b.performanceCounters(true);
    bench_Eigen(&b);
    bench_expr(&b);
    benchnormal(&b);
}
