//  (C) Copyright Matt Borland 2021.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef CCMATH_ROUND_HPP
#define CCMATH_ROUND_HPP

#include <cmath>
#include <type_traits>
#include <stdexcept>

#include "abs.hpp"
#include "isinf.hpp"
#include "isnan.hpp"
#include "modf.hpp"

namespace ccmath {

namespace detail {

// Computes the nearest integer value to arg (in floating-point format),
// rounding halfway cases away from zero, regardless of the current rounding mode.
template <typename T>
inline constexpr T round_impl(T arg) noexcept
{
    T iptr = 0;
    const T x = ccmath::modf(arg, &iptr);
    constexpr T half = T(1)/2;

    if(x >= half && iptr > 0)
    {
        return iptr + 1;
    }
    else if(ccmath::abs(x) >= half && iptr < 0)
    {
        return iptr - 1;
    }
    else
    {
        return iptr;
    }
}

template <typename ReturnType, typename T>
inline constexpr ReturnType int_round_impl(T arg)
{
    const T rounded_arg = round_impl(arg);

    if(rounded_arg > static_cast<T>((std::numeric_limits<ReturnType>::max)()))
    {
        if constexpr (std::is_same_v<ReturnType, long long>)
        {
            throw std::domain_error("Rounded value cannot be represented by a long long type without overflow");
        }
        else
        {
            throw std::domain_error("Rounded value cannot be represented by a long type without overflow");
        }
    }
    else
    {
        return static_cast<ReturnType>(rounded_arg);
    }
}

} // Namespace detail

template <typename Real, std::enable_if_t<!std::is_integral_v<Real>, bool> = true>
inline constexpr Real round(Real arg) noexcept
{
    if( std::is_constant_evaluated() )
    {
        return ccmath::abs(arg) == Real(0) ? arg :
               ccmath::isinf(arg) ? arg :
               ccmath::isnan(arg) ? arg :
               ccmath::detail::round_impl(arg);
    }
    else
    {
        using std::round;
        return round(arg);
    }
}

template <typename Z, std::enable_if_t<std::is_integral_v<Z>, bool> = true>
inline constexpr double round(Z arg) noexcept
{
    return ccmath::round(static_cast<double>(arg));
}

inline constexpr float roundf(float arg) noexcept
{
    return ccmath::round(arg);
}

#ifndef BOOST_MATH_NO_LONG_DOUBLE_MATH_FUNCTIONS
inline constexpr long double roundl(long double arg) noexcept
{
    return ccmath::round(arg);
}
#endif

template <typename Real, std::enable_if_t<!std::is_integral_v<Real>, bool> = true>
inline constexpr long lround(Real arg)
{
    if( std::is_constant_evaluated() )
    {
        return ccmath::abs(arg) == Real(0) ? 0l :
               ccmath::isinf(arg) ? 0l :
               ccmath::isnan(arg) ? 0l :
               ccmath::detail::int_round_impl<long>(arg);
    }
    else
    {
        using std::lround;
        return lround(arg);
    }
}

template <typename Z, std::enable_if_t<std::is_integral_v<Z>, bool> = true>
inline constexpr long lround(Z arg)
{
    return ccmath::lround(static_cast<double>(arg));
}

inline constexpr long lroundf(float arg)
{
    return ccmath::lround(arg);
}

#ifndef BOOST_MATH_NO_LONG_DOUBLE_MATH_FUNCTIONS
inline constexpr long lroundl(long double arg)
{
    return ccmath::lround(arg);
}
#endif

template <typename Real, std::enable_if_t<!std::is_integral_v<Real>, bool> = true>
inline constexpr long long llround(Real arg)
{
    if( std::is_constant_evaluated() )
    {
        return ccmath::abs(arg) == Real(0) ? 0ll :
               ccmath::isinf(arg) ? 0ll :
               ccmath::isnan(arg) ? 0ll :
               ccmath::detail::int_round_impl<long long>(arg);
    }
    else
    {
        using std::llround;
        return llround(arg);
    }
}

template <typename Z, std::enable_if_t<std::is_integral_v<Z>, bool> = true>
inline constexpr long llround(Z arg)
{
    return ccmath::llround(static_cast<double>(arg));
}

inline constexpr long long llroundf(float arg)
{
    return ccmath::llround(arg);
}

#ifndef BOOST_MATH_NO_LONG_DOUBLE_MATH_FUNCTIONS
inline constexpr long long llroundl(long double arg)
{
    return ccmath::llround(arg);
}
#endif

} // Namespaces

#endif // CCMATH_ROUND_HPP
