//  (C) Copyright Matt Borland 2022.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef CCMATH_FMAX_HPP
#define CCMATH_FMAX_HPP

#include <cmath>
#include <float.h>
#include <limits>
#include <type_traits>

#include "isnan.hpp"

namespace ccmath {

namespace detail {

template <typename T>
inline constexpr T fmax_impl(const T x, const T y) noexcept
{
    if (x > y)
    {
        return x;
    }
    else
    {
        return y;
    }
}

} // Namespace detail

template <typename Real, std::enable_if_t<!std::is_integral_v<Real>, bool> = true>
inline constexpr Real fmax(Real x, Real y) noexcept
{
    if ( std::is_constant_evaluated() )
    {
        return ccmath::isnan(x) && ccmath::isnan(y) ? std::numeric_limits<Real>::quiet_NaN() :
               ccmath::isnan(x) ? y :
               ccmath::isnan(y) ? x :
               ccmath::detail::fmax_impl(x, y);
    }
    else
    {
        using std::fmax;
        return fmax(x, y);
    }
}

template <typename T1, typename T2>
inline constexpr auto fmax(T1 x, T2 y) noexcept
{
    if (BOOST_MATH_IS_CONSTANT_EVALUATED(x))
    {
        // If the type is an integer (e.g. epsilon == 0) then set the epsilon value to 1 so that type is at a minimum
        // cast to double
        constexpr auto T1p = std::numeric_limits<T1>::epsilon() > 0 ? std::numeric_limits<T1>::epsilon() : 1;
        constexpr auto T2p = std::numeric_limits<T2>::epsilon() > 0 ? std::numeric_limits<T2>::epsilon() : 1;

        using promoted_type =
                              #ifndef BOOST_MATH_NO_LONG_DOUBLE_MATH_FUNCTIONS
                              std::conditional_t<T1p <= LDBL_EPSILON && T1p <= T2p, T1,
                              std::conditional_t<T2p <= LDBL_EPSILON && T2p <= T1p, T2,
                              #endif
                              std::conditional_t<T1p <= DBL_EPSILON && T1p <= T2p, T1,
                              std::conditional_t<T2p <= DBL_EPSILON && T2p <= T1p, T2, double
                              #ifndef BOOST_MATH_NO_LONG_DOUBLE_MATH_FUNCTIONS
                              >>>>;
                              #else
                              >>;
                              #endif

        return ccmath::fmax(promoted_type(x), promoted_type(y));
    }
    else
    {
        using std::fmax;
        return fmax(x, y);
    }
}

inline constexpr float fmaxf(float x, float y) noexcept
{
    return ccmath::fmax(x, y);
}

#ifndef BOOST_MATH_NO_LONG_DOUBLE_MATH_FUNCTIONS
inline constexpr long double fmaxl(long double x, long double y) noexcept
{
    return ccmath::fmax(x, y);
}
#endif

} // Namespace ccmath

#endif // CCMATH_FMAX_HPP
