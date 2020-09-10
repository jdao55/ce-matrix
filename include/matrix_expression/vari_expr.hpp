#ifndef __VARI_EXPR_H_
#define __VARI_EXPR_H_
// test for implementing without crtp
#include <tuple>
#include <type_traits>
#include <utility>
#include <cstddef>
#include <complex>
namespace vari {
namespace traits {

    template<typename T>
    concept indexable_t = requires(T t, size_t a)
    {
        t(a, a);
    };

    template<typename T>
    concept scaler_t = std::is_arithmetic<T>::value || std::is_same<T, std::complex<float>>::value
                       || std::is_same<T, std::complex<double>>::value;

}// namespace traits
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
    return expr<decltype(f), lhs_t::row_size, rhs_t::col_size, lhs_t, rhs_t>{ f, lhs, rhs };
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


enum class RowOrder {
    colunm,
    row,
};

template<int R_, int C_ = R_, vari::RowOrder order_ = vari::RowOrder::row>
struct mat
{
    constexpr static size_t row_size = R_;
    constexpr static size_t col_size = C_;
    std::array<int, C_ * R_> data;

    template<typename src_t>
    constexpr mat<R_, C_> &operator=(const src_t &src)
    {
        for (auto i = 0; i < R_; i++)
        {
            for (auto j = 0; j < C_; j++) operator()(i, j) = src(i, j);
        }
    }


    template<typename src_t>
    constexpr mat(const src_t &src)
    {
        for (auto i = 0; i < R_; i++)
        {
            for (auto j = 0; j < C_; j++) operator()(i, j) = src(i, j);
        }
    }

    constexpr mat(std::initializer_list<int> l) { std::copy(l.begin(), l.end(), data.begin()); }

    constexpr auto operator[](const size_t i) const { return data[i]; }
    constexpr auto &operator()(const size_t i, const size_t j)
    {
        if constexpr (order_ == vari::RowOrder::row)
            return data[i * C_ + j];
        return data[j * R_ + i];
    }
    constexpr auto operator()(const size_t i, const size_t j) const
    {
        if constexpr (order_ == vari::RowOrder::row)
            return data[i * C_ + j];
        return data[j * R_ + i];
    }
};

template<typename operand>
constexpr auto subscript(const operand &v, const size_t i, const size_t j)
{
    if constexpr (std::is_arithmetic<operand>::value)
    {
        return v;
    }
    return v(i, j);
}


}// namespace vari


#endif// __VARI_EXPR_H_
