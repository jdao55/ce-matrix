#ifndef ALG_H
#define ALG_H
#include "operator.hpp"
#include "vector.hpp"

namespace ce {

//TODO finish implementing linear sovler
template<numeric T, size_t N, size_t M>
constexpr void swap_row(ctmatrix<T,N,M> &mat ,const size_t i, const size_t j)
{
    std::array <int, M> temp{0};
    std::copy(mat.begin()+M*i, mat.begin()+(M*i+M), temp.begin());
    std::copy(mat.begin()+M*j, mat.begin()+M*j+M, mat.begin()+M*i);
    std::copy(temp.begin(), temp.end(), mat.begin()+M*j);
}

}// namespace ce

#endif
