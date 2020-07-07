#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>
#include <algorithm>
#include <array>
#include "numeric_trait.hpp"
namespace ce {

template<traits::numeric T, size_t N, size_t M = N>
struct matrix
{
    std::array<T, N * M> data;

    constexpr matrix() : data(){};
    constexpr matrix(std::initializer_list<T> l) { std::copy(l.begin(), l.end(), data.begin()); }
    constexpr explicit matrix(T init) : data{} { std::fill(data.begin(), data.end(), init); }
    constexpr matrix(const matrix<T, N, M> &cp) = default;
    constexpr matrix(matrix<T, N, M> &&cp) = default;

    constexpr matrix<T, N, M> &operator=(const matrix<T, N, M> &cp) = default;
    constexpr matrix<T, N, M> &operator=(matrix<T, N, M> &&cp) = default;

    template<size_t s>
    [[nodiscard]] constexpr matrix<T, N, s> operator*(const matrix<T, M, s> &rhs) const;

    [[nodiscard]] constexpr matrix<T, N, M> operator*(const T &rhs) const;


    [[nodiscard]] friend constexpr matrix<T, N, M> operator*(const T &lhs, const matrix<T, N, M> &rhs)
    {
        return rhs * lhs;
    }


    [[nodiscard]] constexpr matrix<T, N, M> operator+(const matrix<T, N, M> &rhs) const;

    [[nodiscard]] constexpr matrix<T, N, M> operator-(const matrix<T, N, M> &rhs) const;


    constexpr T &operator[](size_t i) { return data[i]; }
    constexpr const T &operator[](size_t i) const { return data[i]; }

    constexpr const T &operator()(const size_t i, const size_t j) const { return data[i * M + j]; }

    constexpr const T &operator()(const size_t i, const size_t j) { return data[i * M + j]; }

    constexpr const T &at(const size_t i, const size_t j) const { return data[i * M + j]; }
    constexpr T &at(const size_t i, const size_t j) { return data[i * M + j]; }

    constexpr bool operator==(const matrix<T, N, M> &rhs) const { return data == rhs.data; }

    constexpr matrix<T, M, N> transpose() const
    {
        matrix<T, M, N> ret;
        for (size_t i = 0; i < M; i++)
        {
            for (size_t j = 0; j < N; j++)
            {
                ret.at(i, j) = this->at(j, i);
            }
        }
        return ret;
    }
    constexpr const auto begin() const { return data.begin(); }
    constexpr auto begin() { return data.begin(); }

    constexpr const auto end() const { return data.end(); }
    constexpr auto end() { return data.end(); }


    static constexpr matrix<T, N, M> identity()
    {
        static_assert(M == N, "error non square identity matrix");
        matrix<T, N, M> ret{};
        for (size_t i = 0; i < N * M; i += (N + 1))
        {
            ret[i] = static_cast<T>(1);
        }
        return ret;
    }
};
}// namespace ce

#endif
