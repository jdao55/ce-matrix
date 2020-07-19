#ifndef ALG_H
#define ALG_H
#include "matrix_expr.hpp"
#include "operator_expr.hpp"
#include "vector.hpp"

namespace ce {

// TODO finish implementing linear sovler
template<traits::numeric T, size_t N, size_t M>
constexpr void swap_row(matrix_t<T, N, M> &mat, const size_t i, const size_t j)
{
    std::array<int, M> temp{ 0 };
    std::copy(mat.begin() + M * i, mat.begin() + (M * i + M), temp.begin());
    std::copy(mat.begin() + M * j, mat.begin() + M * j + M, mat.begin() + M * i);
    std::copy(temp.begin(), temp.end(), mat.begin() + M * j);
}

template<traits::numeric T, size_t N, size_t M, size_t I>
constexpr matrix_t<T, I + N, M> add_rows(const matrix_t<T, N, M> &lhs, const matrix_t<T, I, M> &rhs)
{
    matrix_t<T, I + N, M> ret;
    std::copy(lhs.begin(), lhs.end(), ret.begin());
    std::copy(rhs.begin(), rhs.end(), ret.begin() + (lhs.data.size()));
    return ret;
}

template<traits::numeric T, size_t N, size_t M>
constexpr matrix_t<T, M, N> transpose(const matrix_t<T, N, M> &mat)
{
    matrix_t<T, M, N> ret;
    for (size_t i = 0; i < M; i++)
    {
        for (size_t j = 0; j < N; j++)
        {
            ret(i, j) = mat(j, i);
        }
    }
    return ret;
}

// reduction operations
template<traits::numeric T, size_t N, size_t M>
constexpr T sum(const matrix_t<T, N, M> &mat)
{
    return std::reduce(mat.begin()+1, mat.end(), mat[0]);
}

template<traits::numeric T, size_t N, size_t M>
constexpr T product(const matrix_t<T, N, M> &mat)
{
    return std::reduce(mat.begin()+1, mat.end(), mat[0], [](const T &a, const T &b) { return a * b; });
}
}// namespace ce

#endif
