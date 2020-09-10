#ifndef __TRAITS_H_
#define __TRAITS_H_

namespace ce::vari::detail::traits {

template<typename T>
concept indexable_t = requires(T t, size_t a)
{
    t(a, a);
};

template<typename T>
concept scaler_t = std::is_arithmetic<T>::value || std::is_same<T, std::complex<float>>::value
                   || std::is_same<T, std::complex<double>>::value;

}// namespace ce::vari::detail::traits


#endif// __TRAITS_H_
