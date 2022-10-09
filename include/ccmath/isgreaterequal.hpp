//  (C) Copyright Matt Borland 2022.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef CCMATH_ISGREATEREQUAL_HPP
#define CCMATH_ISGREATEREQUAL_HPP

#include <cmath>
#include <limits>
#include <type_traits>

#include "isnan.hpp"

namespace ccmath {

template <typename T1, typename T2 = T1>
inline constexpr bool isgreaterequal(T1 x, T2 y) noexcept
{
    if (BOOST_MATH_IS_CONSTANT_EVALUATED(x))
    {
        if (ccmath::isnan(x) || ccmath::isnan(y))
        {
            return false;
        }
        else
        {
            return x >= y;
        }
    }
    else
    {
        using std::isgreaterequal;
        return isgreaterequal(x, y);
    }
}

} // Namespaces

#endif // CCMATH_ISGREATEREQUAL_HPP
