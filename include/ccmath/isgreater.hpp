//  (C) Copyright Matt Borland 2022.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef CCMATH_ISGREATER_HPP
#define CCMATH_ISGREATER_HPP

#include <cmath>
#include <limits>
#include <type_traits>

#include "isnan.hpp"

namespace ccmath {

template <typename T1, typename T2 = T1>
inline constexpr bool isgreater(T1 x, T2 y) noexcept
{
    if ( std::is_constant_evaluated() )
    {
        if (ccmath::isnan(x) || ccmath::isnan(y))
        {
            return false;
        }
        else
        {
            return x > y;
        }
    }
    else
    {
        using std::isgreater;
        return isgreater(x, y);
    }
}

} // Namespaces

#endif // CCMATH_ISGREATER_HPP
