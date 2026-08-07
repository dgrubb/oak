// File: Endian.h
// Author: dgrubb
// Date: 06/08/2026
//
// Provides template function for handling endian
// related issues.

#ifndef ENDIAN_H
#define ENDIAN_H

#include <algorithm>    // std::reverse
#include <array>        // std::array
#include <concepts>     // std::integral
#include <cstddef>      // std::byte
#include <cstring>      // std::memcpy

template <std::integral T>
constexpr T ReverseEndianess(T t) noexcept
{
    std::array<std::byte, sizeof(T)> bytes;
    std::memcpy(bytes.data(), &t, sizeof(T));
    std::reverse(bytes.begin(), bytes.end());

    T reversed;
    std::memcpy(&reversed, bytes.data(), sizeof(T));

    return reversed;
}

#endif // ENDIAN_H
