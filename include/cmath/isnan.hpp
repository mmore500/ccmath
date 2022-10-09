//  (C) Copyright Matt Borland 2021.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef CCMATH_ISNAN
#define CCMATH_ISNAN

#include <cmath>
#include <type_traits>

namespace ccmath {

template <typename T>
inline constexpr bool isnan(T x)
{
    if( std::is_constant_evaluated() )
    {
        return x != x;
    }
    else
    {
        using std::isnan;

        if constexpr (!std::is_integral_v<T>)
        {
            return isnan(x);
        }
        else
        {
            return isnan(static_cast<double>(x));
        }
    }
}

}

#endif // CCMATH_ISNAN
