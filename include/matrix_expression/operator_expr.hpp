#ifndef OPERATOR_EXP_H
#define OPERATOR_EXP_H
#include "matrix_expr.hpp"
#include "numeric_trait.hpp"

namespace ce {
/******************************
 **Addition*******************
 *****************************/
template<typename E1, typename E2, size_t row_c, size_t col_c>
struct matrixSum : public matrix_expr<matrixSum<E1, E2, row_c, col_c>, row_c, col_c>
{
    E1 const &_u;
    E2 const &_v;

    constexpr matrixSum(E1 const &u, E2 const &v) : _u(u), _v(v) {}
    constexpr size_t size() const { return _u.size(); }
    constexpr auto operator()(const size_t i, const size_t j) const { return _u(i, j) + _v(i, j); }
};

template<typename E1, typename E2>
constexpr matrixSum<E1, E2, E1::row_count, E2::col_count> operator+(
    matrix_expr<E1, E1::row_count, E1::col_count> const &u,
    matrix_expr<E2, E2::row_count, E2::col_count> const &v)
{

    static_assert(E1::row_count == E2::row_count, "adding different sized matrices");
    static_assert(E1::col_count == E2::col_count, "adding different sized matrices");
    return matrixSum<E1, E2, E1::row_count, E1::col_count>(*static_cast<const E1 *>(&u), *static_cast<const E2 *>(&v));
}

/******************************
 **subtraction*****************
 *****************************/
template<typename E1, typename E2, size_t row_c, size_t col_c>
struct matrixSub : public matrix_expr<matrixSub<E1, E2, row_c, col_c>, row_c, col_c>
{
    E1 const &_u;
    E2 const &_v;

    constexpr matrixSub(E1 const &u, E2 const &v) : _u(u), _v(v) {}
    constexpr size_t size() const { return _u.size(); }

    constexpr auto operator()(const size_t i, const size_t j) const { return _u(i, j) - _v(i, j); }
};

template<typename E1, typename E2>
constexpr matrixSub<E1, E2, E1::row_count, E2::col_count> operator-(
    matrix_expr<E1, E1::row_count, E1::col_count> const &u,
    matrix_expr<E2, E2::row_count, E2::col_count> const &v)
{
    static_assert(E1::row_count == E2::row_count, "subtracting different sized matrices");
    static_assert(E1::col_count == E2::col_count, "subtraction different sized matrices");
    return matrixSub<E1, E2, E1::row_count, E2::col_count>(*static_cast<const E1 *>(&u), *static_cast<const E2 *>(&v));
}


/******************************
 **multiplication**************
 *****************************/
template<typename E1, typename E2, size_t row_c, size_t col_c>
struct matrixMult : public matrix_expr<matrixMult<E1, E2, row_c, col_c>, row_c, col_c>
{
    E1 const &_u;
    E2 const &_v;

    constexpr matrixMult(E1 const &u, E2 const &v) : _u(u), _v(v) {}
    constexpr size_t size() const { return _u.size(); }

    constexpr auto operator()(const size_t i, const size_t j) const
    {
        auto ret = _u(i, 0) * _v(0, j);
        for (size_t k = 1; k < E1::col_count; ++k)
        {
            ret += _u(i, k) * _v(k, j);
        }
        return ret;
    }
};

template<typename E1, typename E2>
constexpr matrixMult<E1, E2, E1::row_count, E2::col_count> operator*(
    matrix_expr<E1, E1::row_count, E1::col_count> const &u,
    matrix_expr<E2, E2::row_count, E2::col_count> const &v)
{
    static_assert(E1::col_count == E2::row_count, "Multiplication between matrices of different col size and row size");
    return matrixMult<E1, E2, E1::row_count, E2::col_count>(*static_cast<const E1 *>(&u), *static_cast<const E2 *>(&v));
}

/*****************************
**plus equal/minus************
*****************************/
template<traits::numeric T, typename E2, size_t N, size_t M>
constexpr void operator+=(matrix_t<T, N, M> &lhs, const E2 &rhs)
{

    static_assert(N == E2::row_count, "Addition between different sized matrices");
    static_assert(M == E2::col_count, "Addition between different sized matrices");
    for (size_t i = 0; i < N; i++)
    {
        for (size_t j = 0; j < M; ++j)
        {
            lhs.at(i, j) = lhs.at(i, j) + rhs(i, j);
        }
    }
}

template<traits::numeric T, typename E2, size_t N, size_t M>
constexpr void operator-=(matrix_t<T, N, M> &lhs, const E2 &rhs)
{

    static_assert(N == E2::row_count, "Addition between different sized matrices");
    static_assert(M == E2::col_count, "Addition between different sized matrices");
    for (size_t i = 0; i < N; i++)
    {
        for (size_t j = 0; j < M; ++j)
        {
            lhs.at(i, j) = lhs.at(i, j) - rhs(i, j);
        }
    }
}
/*****************************
**scaler operators************
*****************************/

template<traits::numeric T, size_t N, size_t M>
constexpr matrix_t<T, N, M> operator*(const matrix_t<T, N, M> lhs, const T &rhs)
{
    matrix_t<T, N, M> ret;
    std::ranges::transform(lhs, ret.begin(), [&rhs](const auto &elem) { return elem * rhs; });
    return ret;
}


template<traits::numeric T, size_t N, size_t M>
constexpr matrix_t<T, N, M> operator*(const T &lhs, const matrix_t<T, N, M> rhs)
{
    return rhs * lhs;
}


template<traits::numeric T, size_t N, size_t M>
constexpr matrix_t<T, N, M> operator/(const matrix_t<T, N, M> lhs, const T &rhs)
{
    matrix_t<T, N, M> ret;
    std::ranges::transform(lhs, ret.begin(), [&rhs](const auto &elem) { return elem / rhs; });
    return ret;
}


template<traits::numeric T, size_t N, size_t M>
constexpr matrix_t<T, N, M> operator/(const T &lhs, const matrix_t<T, N, M> rhs)
{
    return rhs / lhs;
}

}// namespace ce
#endif
