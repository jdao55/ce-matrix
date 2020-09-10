#ifndef TRAITS_H
#define TRAITS_H

namespace ce::crtp::traits {

template<typename T>
concept Addable = requires(T x)
{
    x + x;
};

template<typename T>
concept Subractable = requires(T x)
{
    x - x;
};

template<typename T>
concept Multipliable = requires(T x)
{
    x *x;
};

template<typename T>
concept Dividable = requires(T x)
{
    x / x;
};

template<typename T>
concept numeric = Addable<T> &&Subractable<T> &&Multipliable<T> &&Dividable<T>;
}// namespace ce::crtp::traits

#endif
