#ifndef __UTIL_H_
#define __UTIL_H_

#include <complex>
#include <type_traits>

namespace ce::vari::utils {
template<typename operand>
constexpr auto subscript(const operand &v, const size_t i, const size_t j)
{
    if constexpr (std::is_arithmetic<operand>::value || std::is_same<operand, std::complex<float>>::value
                  || std::is_same<operand, std::complex<double>>::value)
    {
        return v;
    }
    else
        return v(i, j);
}
}// namespace ce::vari::utils

#endif// __UTIL_H_
