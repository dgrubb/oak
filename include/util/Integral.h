// File: Integral.h
// Author: dgrubb
// Date: 16/11/2023
//
// Provides simple conversation of enum class to underlying
// integral types. Allows for nicer syntax than leaving
// static_cast all over the code. For example, instead of:
//
// enum Foo
// {
//      BAR = 0
// }
// auto result = compute(static_cast<unsigned int>(BAR);
//
// It's possible to avoid poluting namespace with enum names
// and not having to know the underlying type with each usage
// of static_cast. E.g.,:
//
// enum class Foo : int
// {
//      BAR = 0
// }
// auto result = compute(ToIntegral(Foo::BAR));
//
// Found at:
// https://stackoverflow.com/questions/14589417/can-an-enum-class-be-converted-to-the-underlying-type

#ifndef INTEGRAL_H
#define INTEGRAL_H

#include <type_traits> // std::underlying_type

template <typename T>
constexpr auto ToIntegral(T t) -> typename std::underlying_type<T>::type
{
    return static_cast<typename std::underlying_type<T>::type>(t);
}

#endif // INTEGRAL_H
