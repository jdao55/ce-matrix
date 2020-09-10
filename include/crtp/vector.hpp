#ifndef CE_VECTOR_H
#define CE_VECTOR_H

#include "operator_expr.hpp"
#include "numeric_trait.hpp"

#include <numeric>

namespace ce::crtp {

template<traits::numeric T, size_t N>
using vector = matrix_t<T, N, 1>;

namespace vec {
    template<traits::numeric T, size_t N>
    constexpr T dot_product(const vector<T, N> &lhs, const vector<T, N> &rhs)
    {
        return std::inner_product(lhs.begin(), lhs.end(), rhs.begin(), 0);
    }

    template<traits::numeric T>
    constexpr vector<T, 3> cross_product(const vector<T, 3> &lhs, const vector<T, 3> &rhs)
    {
        return vector<T, 3>{
            lhs[1] * rhs[2] - lhs[2] * rhs[1], -(lhs[0] * rhs[2] - lhs[2] * rhs[0]), (lhs[0] * rhs[1] - lhs[1] * rhs[0])
        };
    }
}// namespace vec

}// namespace ce::crtp
#endif
