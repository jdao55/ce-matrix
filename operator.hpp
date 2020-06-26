#ifndef OPERATOR_H
#define OPERATOR_H
#include "matrix.hpp"
#include "numeric_trait.hpp"
namespace ce {

template<numeric T, size_t n, size_t m>
constexpr ctmatrix<T, n, m> ctmatrix<T, n, m>::operator*(const T &rhs) const
{
    ctmatrix<T, n, m> ret;
    for (size_t i = 0; i < n * m; i++)
    {
        ret.data[i] = data[i] * rhs;
    }
    return ret;
}

template<numeric T, size_t n, size_t m>
template<size_t s>
constexpr ctmatrix<T, n, s> ctmatrix<T, n, m>::operator*(const ctmatrix<T, m, s> &rhs) const
{
    ctmatrix<T, n, s> ret;
    for (size_t i = 0; i < n; ++i)
    {
        for (size_t j = 0; j < s; ++j)
        {
            for (size_t k = 0; k < m; ++k)
            {
                ret.at(i, j) += this->at(i, k) * rhs.at(k, j);
            }
        }
    }
    return ret;
}

template<numeric T, size_t n, size_t m>
constexpr ctmatrix<T, n, m> ctmatrix<T, n, m>::operator+(const ctmatrix<T, n, m> &rhs) const
{
    ctmatrix<T, n, m> ret;
    for (auto i = 0; i < n * m; i++)
    {
        ret.data[i] = data[i] + rhs.data[i];
    }
    return ret;
}


template<numeric T, size_t n, size_t m>
[[nodiscard]] constexpr ctmatrix<T, n, m> ctmatrix<T, n, m>::operator-(const ctmatrix<T, n, m> &rhs) const
{
    ctmatrix<T, n, m> ret;
    for (size_t i = 0; i < n * m; i++)
    {
        ret.data[i] = data[i] - rhs.data[i];
    }
    return ret;
}

}// namespace ce
#endif
