#ifndef ALG_H
#define ALG_H
#include "matrix.hpp"
#include "operator.hpp"
#include "vector.hpp"

namespace ce {

// TODO finish implementing linear sovler
template<traits::numeric T, size_t N, size_t M>
constexpr void swap_row(matrix<T, N, M> &mat, const size_t i, const size_t j)
{
    std::array<int, M> temp{ 0 };
    std::copy(mat.begin() + M * i, mat.begin() + (M * i + M), temp.begin());
    std::copy(mat.begin() + M * j, mat.begin() + M * j + M, mat.begin() + M * i);
    std::copy(temp.begin(), temp.end(), mat.begin() + M * j);
}

template<traits::numeric T, size_t N, size_t M, size_t I>
constexpr matrix<T, I+N,M> add_rows(const matrix<T, N,M> &lhs, const matrix<T,I,M>& rhs) {
    matrix<T, I+N,M> ret;
    std::copy(lhs.begin(), lhs.end(), ret.begin());
    std::copy(rhs.begin(), rhs.end(), ret.begin()+(lhs.data.size()));
    return ret;

}

}// namespace ce

#endif
