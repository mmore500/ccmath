//  (C) Copyright Matt Borland 2021.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef CCMATH_ISFINITE
#define CCMATH_ISFINITE

#include <cmath>
#include <type_traits>

#include "isinf.hpp"
#include "isnan.hpp"

namespace ccmath {

template <typename T>
inline constexpr bool isfinite(T x)
{
    if( std::is_constant_evaluated() )
    {
        // bool isfinite (IntegralType arg) is a set of overloads accepting the arg argument of any integral type
        // equivalent to casting the integral argument arg to double (e.g. static_cast<double>(arg))
        if constexpr (std::is_integral_v<T>)
        {
            return !ccmath::isinf(static_cast<double>(x)) && !ccmath::isnan(static_cast<double>(x));
        }
        else
        {
            return !ccmath::isinf(x) && !ccmath::isnan(x);
        }
    }
    else
    {
        using std::isfinite;

        if constexpr (!std::is_integral_v<T>)
        {
            return isfinite(x);
        }
        else
        {
            return isfinite(static_cast<double>(x));
        }
    }
}

}

#endif // CCMATH_ISFINITE
