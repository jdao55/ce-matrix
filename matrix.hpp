#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>
#include <algorithm>
#include <array>

namespace ce {

template<typename T, size_t n, size_t m> struct ctmatrix
{
    std::array<T, n * m> data;

    constexpr ctmatrix() : data(){};
    constexpr ctmatrix(std::initializer_list<T> l) { std::copy(l.begin(), l.end(), data.begin()); }
    constexpr ctmatrix(const ctmatrix<T, n, m> &cp) = default;
    constexpr ctmatrix(ctmatrix<T, n, m> &&cp) = default;

    constexpr ctmatrix<T, n, m> &operator=(const ctmatrix<T, n, m> &cp) = default;
    constexpr ctmatrix<T, n, m> &operator=(ctmatrix<T, n, m> &&cp) = default;

    template<size_t s>[[nodiscard]] constexpr ctmatrix<T, n, s> operator*(const ctmatrix<T, m, s> &rhs) const;

    [[nodiscard]] constexpr ctmatrix<T, n, m> operator*(const T &rhs) const;


    [[nodiscard]] friend constexpr ctmatrix<T, n, m> operator*(const T &lhs, const ctmatrix<T, n, m> &rhs)
    {
        return rhs * lhs;
    }


    [[nodiscard]] constexpr ctmatrix<T, n, m> operator+(const ctmatrix<T, n, m> &rhs) const;

    [[nodiscard]] constexpr ctmatrix<T, n, m> operator-(const ctmatrix<T, n, m> &rhs) const;


    constexpr T &operator[](size_t i) { return data[i]; }
    constexpr const T &operator[](size_t i) const { return data[i]; }

    constexpr const T &operator()(const size_t i, const size_t j) const { return data[i * m + j]; }

    constexpr const T &operator()(const size_t i, const size_t j) { return data[i * m + j]; }

    constexpr const T &at(const size_t i, const size_t j) const { return data[i * m + j]; }
    constexpr T &at(const size_t i, const size_t j) { return data[i * m + j]; }

    constexpr ctmatrix<T, m, n> transpose() const
    {
        ctmatrix<T, m, n> ret;
        for (size_t i = 0; i < m; i++)
        {
            for (size_t j = 0; j < n; j++)
            {
                ret.at(i, j) = this->at(j, i);
            }
        }
        return ret;
    }
};
}// namespace ce

#endif
