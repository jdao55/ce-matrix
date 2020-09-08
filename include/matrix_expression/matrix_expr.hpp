#ifndef MATRIX_EXPR_H
#define MATRIX_EXPR_H

#include <algorithm>
#include <array>
#include "numeric_trait.hpp"
namespace ce {

template<typename T, size_t Row_count_, size_t Col_count_>
struct matrix_expr
{
    static constexpr size_t row_count = Row_count_;
    static constexpr size_t col_count = Col_count_;
    // constexpr data_t operator[](const size_t i) const { return static_cast<T const &>(*this)[i]; }
    constexpr auto operator()(const size_t i, const size_t j) const { return static_cast<T const &>(*this)(i, j); }
    constexpr size_t size() const { return static_cast<T const &>(*this).size(); }
};


template<traits::numeric data_t, size_t row_c, size_t col_c>
struct matrix_t : public matrix_expr<matrix_t<data_t, row_c, col_c>, row_c, col_c>
{
    std::array<data_t, row_c * col_c> data;

    // ctors
    constexpr matrix_t() : data(){};
    constexpr matrix_t(std::initializer_list<data_t> l) { std::copy(l.begin(), l.end(), data.begin()); }
    constexpr explicit matrix_t(data_t init) : data{} { std::fill(data.begin(), data.end(), init); }
    constexpr matrix_t(std::array<data_t, row_c * col_c> arr) : data(arr) {}
    constexpr matrix_t(std::array<data_t, row_c * col_c> &&arr) : data(arr) {}
    constexpr matrix_t(const matrix_t<data_t, row_c, col_c> &cp) = default;
    constexpr matrix_t(matrix_t<data_t, row_c, col_c> &&cp) = default;
    // matrix info
    constexpr size_t size() const { return row_c * col_c; }

    // expression ctor
    template<typename E>
    constexpr matrix_t(matrix_expr<E, row_c, col_c> const &expr) : data{}
    {
        for (size_t i = 0; i < row_c; ++i)
        {
            for (size_t j = 0; j < col_c; ++j)
            {
                at(i, j) = expr(i, j);
            }
        }
    }

    // element access
    constexpr data_t &operator[](size_t i) { return data[i]; }
    constexpr const data_t operator[](size_t i) const { return data[i]; }

    constexpr auto operator()(const size_t i, const size_t j) const { return data[i * col_c + j]; }
    constexpr auto &operator()(const size_t i, const size_t j) { return data[i * col_c + j]; }

    constexpr const data_t &at(const size_t i, const size_t j) const { return data[i * col_c + j]; }
    constexpr data_t &at(const size_t i, const size_t j) { return data[i * col_c + j]; }

    constexpr const auto begin() const { return data.begin(); }
    constexpr auto begin() { return data.begin(); }

    constexpr const auto end() const { return data.end(); }
    constexpr auto end() { return data.end(); }


    // utils
    constexpr matrix_t<data_t, col_c, row_c> transpose() const
    {
        matrix_t<data_t, col_c, row_c> ret;
        for (size_t i = 0; i < col_c; i++)
        {
            for (size_t j = 0; j < row_c; j++)
            {
                ret(i, j) = this->at(j, i);
            }
        }
        return ret;
    }

    static constexpr matrix_t<data_t, row_c, col_c> identity()
    {
        static_assert(col_c == row_c, "error non square identity matrix");
        matrix_t<data_t, row_c, col_c> ret{};
        for (size_t i = 0; i < row_c * col_c; i += (row_c + 1))
        {
            ret[i] = static_cast<data_t>(1);
        }
        return ret;
    }
};


}// namespace ce
#endif
