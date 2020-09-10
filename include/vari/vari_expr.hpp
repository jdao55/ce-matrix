#ifndef __VARI_EXPR_H_
#define __VARI_EXPR_H_
// test for implementing without crtp
#include <tuple>
#include <type_traits>
#include <utility>
#include <complex>
#include "traits.hpp"
#include "util.hpp"
namespace ce::vari {

using namespace detail;
using namespace utils;
template<typename callable, size_t R_, size_t C_, class... operands>
class expr
{
    std::tuple<operands const &...> args_;
    callable f_;

  public:
    constexpr static size_t row_size = R_;
    constexpr static size_t col_size = C_;
    constexpr expr(callable f, operands const &... args) : args_(args...), f_(f) {}
    constexpr auto operator()(const size_t i, const size_t j) const
    {
        const auto call_at_index = [this, i, j](const operands &... a) { return f_(subscript(a, i, j)...); };
        return std::apply(call_at_index, args_);
    }
};

template<size_t R_, size_t C_, typename lhs_t, typename rhs_t>
class multexpr
{
    const lhs_t &lhs;
    const rhs_t &rhs;

  public:
    constexpr static size_t row_size = R_;
    constexpr static size_t col_size = C_;
    constexpr multexpr(const lhs_t &l, const rhs_t &r) : lhs(l), rhs(r)
    {
        static_assert(lhs_t::col_size == rhs_t::row_size, "Error lhs::colunm_size != rhs::row_size");
    }
    constexpr auto operator()(const size_t i, const size_t j) const
    {
        auto ret = lhs(i, 0) * rhs(0, j);
        for (size_t k = 1; k < lhs_t::col_size; ++k)
        {
            ret += lhs(i, k) * rhs(k, j);
        }
        return ret;
    }
};


template<typename lhs_t, typename rhs_t>
    requires(traits::indexable_t<lhs_t> &&traits::scaler_t<rhs_t>)
    || (traits::scaler_t<lhs_t> && traits::indexable_t<rhs_t>)constexpr auto operator*(const lhs_t &lhs,
        const rhs_t &rhs)
{
    constexpr auto f = [](const auto &l, const auto &r) { return l * r; };
    return expr<decltype(f), lhs_t::row_size, lhs_t::col_size, lhs_t, rhs_t>{ f, lhs, rhs };
}


template<typename lhs_t, typename rhs_t>
requires(traits::scaler_t<lhs_t> &&traits::indexable_t<rhs_t>) constexpr auto operator*(const lhs_t &lhs,
    const rhs_t &rhs)
{
    constexpr auto f = [](const auto &l, const auto &r) { return l * r; };
    return expr<decltype(f), rhs_t::row_size, rhs_t::col_size, lhs_t, rhs_t>{ f, lhs, rhs };
}


template<typename lhs_t, typename rhs_t>
requires traits::indexable_t<lhs_t> &&traits::indexable_t<rhs_t> constexpr auto operator*(const lhs_t &lhs,
    const rhs_t &rhs)
{
    return multexpr<lhs_t::row_size, rhs_t::col_size, lhs_t, rhs_t>(lhs, rhs);
}

template<typename lhs_t, typename rhs_t>
requires traits::indexable_t<lhs_t> &&traits::indexable_t<rhs_t> constexpr auto operator+(const lhs_t &lhs,
    const rhs_t &rhs)
{
    constexpr auto f = [](const auto &l, const auto &r) { return l + r; };
    return expr<decltype(f), lhs_t::row_size, rhs_t::col_size, lhs_t, rhs_t>(f, lhs, rhs);
}


template<typename lhs_t, typename rhs_t>
constexpr auto operator-(const lhs_t &lhs, const rhs_t &rhs)
{
    constexpr auto f = [](const auto &l, const auto &r) { return l - r; };
    return expr<decltype(f), lhs_t::row_size, rhs_t::col_size, lhs_t, rhs_t>(f, lhs, rhs);
}


}// namespace ce::vari

#endif// __VARI_EXPR_H_
