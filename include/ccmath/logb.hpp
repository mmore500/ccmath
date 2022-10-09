//  (C) Copyright Matt Borland 2021.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef CCMATH_LOGB_HPP
#define CCMATH_LOGB_HPP

#include <cmath>
#include <limits>
#include <type_traits>

#include "frexp.hpp"
#include "isinf.hpp"
#include "isnan.hpp"
#include "abs.hpp"

namespace ccmath {

namespace detail {

// The value of the exponent returned by std::logb is always 1 less than the exponent returned by
// std::frexp because of the different normalization requirements: for the exponent e returned by std::logb,
// |arg*r^-e| is between 1 and r (typically between 1 and 2), but for the exponent e returned by std::frexp,
// |arg*2^-e| is between 0.5 and 1.
template <typename T>
inline constexpr T logb_impl(T arg) noexcept
{
    int exp = 0;
    ccmath::frexp(arg, &exp);

    return exp - 1;
}

} // Namespace detail

template <typename Real, std::enable_if_t<!std::is_integral_v<Real>, bool> = true>
inline constexpr Real logb(Real arg) noexcept
{
    if( std::is_constant_evaluated() )
    {
        return ccmath::abs(arg) == Real(0) ? -std::numeric_limits<Real>::infinity() :
               ccmath::isinf(arg) ? std::numeric_limits<Real>::infinity() :
               ccmath::isnan(arg) ? std::numeric_limits<Real>::quiet_NaN() :
               ccmath::detail::logb_impl(arg);
    }
    else
    {
        using std::logb;
        return logb(arg);
    }
}

template <typename Z, std::enable_if_t<std::is_integral_v<Z>, bool> = true>
inline constexpr double logb(Z arg) noexcept
{
    return ccmath::logb(static_cast<double>(arg));
}

inline constexpr float logbf(float arg) noexcept
{
    return ccmath::logb(arg);
}

#ifndef BOOST_MATH_NO_LONG_DOUBLE_MATH_FUNCTIONS
inline constexpr long double logbl(long double arg) noexcept
{
    return ccmath::logb(arg);
}
#endif

} // Namespaces

#endif // CCMATH_LOGB_HPP
