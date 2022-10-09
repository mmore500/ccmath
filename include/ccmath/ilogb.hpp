//  (C) Copyright Matt Borland 2021.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef CCMATH_ILOGB_HPP
#define CCMATH_ILOGB_HPP

#include <cmath>
#include <climits>
#include <type_traits>

#include "logb.hpp"
#include "isinf.hpp"
#include "isnan.hpp"
#include "abs.hpp"

namespace ccmath {

// If arg is not zero, infinite, or NaN, the value returned is exactly equivalent to static_cast<int>(std::logb(arg))
template <typename Real, std::enable_if_t<!std::is_integral_v<Real>, bool> = true>
inline constexpr int ilogb(Real arg) noexcept
{
    if( std::is_constant_evaluated() )
    {
        return ccmath::abs(arg) == Real(0) ? FP_ILOGB0 :
               ccmath::isinf(arg) ? INT_MAX :
               ccmath::isnan(arg) ? FP_ILOGBNAN :
               static_cast<int>(ccmath::logb(arg));
    }
    else
    {
        using std::ilogb;
        return ilogb(arg);
    }
}

template <typename Z, std::enable_if_t<std::is_integral_v<Z>, bool> = true>
inline constexpr int ilogb(Z arg) noexcept
{
    return ccmath::ilogb(static_cast<double>(arg));
}

inline constexpr int ilogbf(float arg) noexcept
{
    return ccmath::ilogb(arg);
}

#ifndef BOOST_MATH_NO_LONG_DOUBLE_MATH_FUNCTIONS
inline constexpr int ilogbl(long double arg) noexcept
{
    return ccmath::ilogb(arg);
}
#endif

} // Namespaces

#endif // CCMATH_ILOGB_HPP
