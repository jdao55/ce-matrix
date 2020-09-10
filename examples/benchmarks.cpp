#include "nanobench.h"
#include <Eigen/Dense>
#include <random>
#include <iostream>
#include <atomic>
#include <memory>
#include "../include/cematrix.hpp"
#include "../include/noexpr/matrix.hpp"
#include "../include/noexpr/operator.hpp"
#include "../include/vari/matrix.hpp"
#include "../include/vari/vari_expr.hpp"

constexpr auto N = 8;
using scaler_t = int;
using fmatNN_crtp = ce::crtp::matrix_t<scaler_t, N, N>;
using fmatNN_noexpr = ce::noexpr::matrix<scaler_t, N, N>;
using fmatNN_vari = ce::vari::matrix_t<scaler_t, N, N>;

std::random_device rd;
ankerl::nanobench::Rng e2(rd());
std::uniform_int_distribution<scaler_t> dist(-5000, 5000);


template<typename mat_t>
auto rand_mat()
{
    std::array<scaler_t, N * N> ret{};
    for (auto &element : ret)
    {
        element = dist(e2);
    }
    mat_t ret_mat{};
    ret_mat.data = ret;
    return ret_mat;
}

void bench_noexpr(ankerl::nanobench::Bench *bench)
{
    const fmatNN_noexpr a = rand_mat<fmatNN_noexpr>();
    const fmatNN_noexpr b = rand_mat<fmatNN_noexpr>();
    const fmatNN_noexpr c = rand_mat<fmatNN_noexpr>();

    bench->run("noexpr", [&]() {
        fmatNN_noexpr res = (a * b + a * c);
        ankerl::nanobench::doNotOptimizeAway(res);
    });
}

void bench_crtp(ankerl::nanobench::Bench *bench)
{
    const fmatNN_crtp a = rand_mat<fmatNN_crtp>();
    const fmatNN_crtp b = rand_mat<fmatNN_crtp>();
    const fmatNN_crtp c = rand_mat<fmatNN_crtp>();

    bench->run("crtp", [&]() {
        fmatNN_crtp res = (a * b + a * c);
        ankerl::nanobench::doNotOptimizeAway(res);
    });
}
void bench_vari(ankerl::nanobench::Bench *bench)
{
    const fmatNN_vari a = rand_mat<fmatNN_vari>();
    const fmatNN_vari b = rand_mat<fmatNN_vari>();
    const fmatNN_vari c = rand_mat<fmatNN_vari>();

    bench->run("vari", [&]() {
        fmatNN_vari res = (a * b + a * c);
        ankerl::nanobench::doNotOptimizeAway(res);
    });
}
void bench_Eigen(ankerl::nanobench::Bench *bench)
{
    const Eigen::Matrix<scaler_t, N, N> a = Eigen::Matrix<scaler_t, N, N>::Random();
    const Eigen::Matrix<scaler_t, N, N> b = Eigen::Matrix<scaler_t, N, N>::Random();
    const Eigen::Matrix<scaler_t, N, N> c = Eigen::Matrix<scaler_t, N, N>::Random();

    bench->run("Eigen", [&]() {
        Eigen::Matrix<scaler_t, N, N> res = (a * b + a * c);
        ankerl::nanobench::doNotOptimizeAway(res);
    });
}

int main()
{

    ankerl::nanobench::Bench b;
    b.title("Expression templates benchmark").unit("expr").warmup(500).relative(true);
    b.performanceCounters(true);
    bench_Eigen(&b);
    bench_crtp(&b);
    bench_noexpr(&b);
    bench_vari(&b);
}
