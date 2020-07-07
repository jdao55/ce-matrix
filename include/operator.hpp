#ifndef OPERATOR_H
#define OPERATOR_H
#include "matrix.hpp"
#include "numeric_trait.hpp"

namespace ce {

template<traits::numeric T, size_t n, size_t m>
constexpr matrix<T, n, m> matrix<T, n, m>::operator*(const T &rhs) const
{
    matrix<T, n, m> ret;
    for (size_t i = 0; i < n * m; i++)
    {
        ret.data[i] = data[i] * rhs;
    }
    return ret;
}

template<traits::numeric T, size_t n, size_t m>
template<size_t s>
constexpr matrix<T, n, s> matrix<T, n, m>::operator*(const matrix<T, m, s> &rhs) const
{
    matrix<T, n, s> ret;
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

template<traits::numeric T, size_t n, size_t m>
constexpr matrix<T, n, m> matrix<T, n, m>::operator+(const matrix<T, n, m> &rhs) const
{
    matrix<T, n, m> ret;
    for (size_t i = 0; i < n * m; i++)
    {
        ret.data[i] = data[i] + rhs.data[i];
    }
    return ret;
}


template<traits::numeric T, size_t n, size_t m>
[[nodiscard]] constexpr matrix<T, n, m> matrix<T, n, m>::operator-(const matrix<T, n, m> &rhs) const
{
    matrix<T, n, m> ret;
    for (size_t i = 0; i < n * m; i++)
    {
        ret.data[i] = data[i] - rhs.data[i];
    }
    return ret;
}

}// namespace ce
#endif
