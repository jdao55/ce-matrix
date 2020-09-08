#ifndef __VARI_EXPR_H_
#define __VARI_EXPR_H_
// test for implementing without crtp
#include <tuple>
#include <type_traits>
#include <utility>
#include <cstddef>
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

template<typename callable, size_t R_, size_t C_, typename rhs_t, typename lhs_t>
requires traits::indexable_t<lhs_t> &&traits::indexable_t<rhs_t> class multexpr
{
    callable f_;
    rhs_t &rhs;
    lhs_t &lhs;

  public:
    constexpr static size_t row_size = R_;
    constexpr static size_t col_size = C_;
    constexpr multexpr(callable f, rhs_t &r, lhs_t &l) : rhs(r), lhs(l), f_(f)
    {
        static_assert(lhs_t::col_size == rhs_t::row_size, "Error lhs::colunm_size != rhs::row_size");
    }
    constexpr auto operator()(const size_t i, const size_t j) const
    {
        auto ret = lhs(i, 0) * rhs(0, j);
        for (size_t k = 1; k < lhs_t::col_count; ++k)
        {
            ret += lhs(i, k) * rhs(k, j);
        }
        return ret;
    }
};

template<typename LHS, typename RHS>
requires constexpr auto operator*(const LHS &lhs, const RHS &rhs)
{
    return expr{ [](const auto &l, const auto &r) { return l * r; }, lhs, rhs };
}


template<typename LHS, typename RHS>
requires traits::indexable_t<LHS> &&traits::indexable_t<RHS> constexpr auto operator*(const LHS &lhs, const RHS &rhs)
{
    return multexpr{ [](const auto &l, const auto &r) { return l * r; }, lhs, rhs };
}

template<typename LHS, typename RHS>
constexpr auto operator+(const LHS &lhs, const RHS &rhs)
{
    return expr{ [](const auto &l, const auto &r) { return l + r; }, lhs, rhs };
}

enum class RowOrder {
    colunm,
    row,
};
}// namespace vari
template<int R_, int C_ = R_, vari::RowOrder order_ = vari::RowOrder::row>
struct mat
{
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
