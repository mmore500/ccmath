//  (C) Copyright Matt Borland 2022.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef CCMATH_ISUNORDERED_HPP
#define CCMATH_ISUNORDERED_HPP

#include <cmath>

#include "isnan.hpp"

namespace ccmath {

template <typename T>
inline constexpr bool isunordered(const T x, const T y) noexcept
{
    if( std::is_constant_evaluated() )
    {
        return ccmath::isnan(x) || ccmath::isnan(y);
    }
    else
    {
        using std::isunordered;
        return isunordered(x, y);
    }
}

} // Namespaces

#endif // CCMATH_ISUNORDERED_HPP
