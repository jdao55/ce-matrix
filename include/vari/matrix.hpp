#ifndef __MATRIX_H_
#define __MATRIX_H_
#include <array>
#include <cstddef>
namespace ce::vari {

enum class RowOrder {
    colunm,
    row,
};

template<typename scaler_t, size_t R_, size_t C_ = R_, vari::RowOrder order_ = vari::RowOrder::row>
struct matrix_t
{
    constexpr static size_t row_size = R_;
    constexpr static size_t col_size = C_;
    std::array<scaler_t, C_ * R_> data;

    template<typename src_t>
    constexpr matrix_t<scaler_t, R_, C_> &operator=(const src_t &src)
    {
        for (auto i = 0; i < R_; i++)
        {
            for (auto j = 0; j < C_; j++) operator()(i, j) = src(i, j);
        }
    }


    template<typename src_t>
    constexpr matrix_t(const src_t &src)
    {
        for (size_t i = 0; i < R_; i++)
        {
            for (size_t j = 0; j < C_; j++) operator()(i, j) = src(i, j);
        }
    }

    constexpr matrix_t(std::initializer_list<int> l) { std::copy(l.begin(), l.end(), data.begin()); }

    constexpr auto operator[](const size_t i) const { return data[i]; }
    constexpr auto &operator()(const size_t i, const size_t j)
    {
        if constexpr (order_ == vari::RowOrder::row)
            return data[i * C_ + j];
        return data[j * R_ + i];
    }
    constexpr auto operator()(const size_t i, const size_t j) const
    {
        if constexpr (order_ == vari::RowOrder::row)
            return data[i * C_ + j];
        return data[j * R_ + i];
    }

    constexpr auto cbegin() const { return data.cbegin(); }
    constexpr auto cend() const { return data.cend(); }
    constexpr auto begin() { return data.begin(); }
    constexpr auto end() { return data.end(); }
};

}// namespace ce::vari

#endif// __MATRIX_H_
