//  (C) Copyright Matt Borland 2021.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef CCMATH_FPCLASSIFY
#define CCMATH_FPCLASSIFY

#include <cmath>
#include <limits>
#include <type_traits>

#include "abs.hpp"
#include "isinf.hpp"
#include "isnan.hpp"
#include "isfinite.hpp"

namespace ccmath {

template <typename T, std::enable_if_t<!std::is_integral_v<T>, bool> = true>
inline constexpr int fpclassify(T x)
{
    if( std::is_constant_evaluated() )
    {
        return ccmath::isnan(x) ? FP_NAN :
               ccmath::isinf(x) ? FP_INFINITE :
               ccmath::abs(x) == T(0) ? FP_ZERO :
               ccmath::abs(x) > 0 && ccmath::abs(x) < (std::numeric_limits<T>::min)() ? FP_SUBNORMAL : FP_NORMAL;
    }
    else
    {
        using std::fpclassify;
        return fpclassify(x);
    }
}

template <typename Z, std::enable_if_t<std::is_integral_v<Z>, bool> = true>
inline constexpr int fpclassify(Z x)
{
    return ccmath::fpclassify(static_cast<double>(x));
}

}

#endif // CCMATH_FPCLASSIFY
