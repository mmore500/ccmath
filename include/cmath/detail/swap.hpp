//  (C) Copyright Matt Borland 2021.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef CCMATH_DETAIL_SWAP_HPP
#define CCMATH_DETAIL_SWAP_HPP

namespace boost::math::ccmath::detail {

template <typename T>
inline constexpr void swap(T& x, T& y) noexcept
{
    T temp = x;
    x = y;
    y = temp;
}

}

#endif // CCMATH_DETAIL_SWAP_HPP
