#ifndef VARI_VECTOR_H
#define VARI_VECTOR_H

#include "matrix.hpp"
#include "traits.hpp"

#include <numeric>

namespace ce::vari {

template<detail::traits::scaler_t T, size_t N>
using vector_t = matrix_t<T, N, 1ul>;


template<typename T, size_t N>
constexpr auto dot_product(const vector_t<T, N> &lhs, const vector_t<T, N> &rhs)
{
    return std::inner_product(lhs.cbegin() + 1, lhs.cend(), rhs.cbegin() + 1, lhs[0] * rhs[0]);
}

template<detail::traits::scaler_t T>
constexpr auto cross_product(const vector_t<T, 3> &lhs, const vector_t<T, 3> &rhs)
{
    return vector_t<T, 3>{
        lhs[1] * rhs[2] - lhs[2] * rhs[1], -(lhs[0] * rhs[2] - lhs[2] * rhs[0]), (lhs[0] * rhs[1] - lhs[1] * rhs[0])
    };
}

}// namespace ce::vari
#endif
