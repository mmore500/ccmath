//  (C) Copyright Matt Borland 2021.
//  (C) Copyright John Maddock 2021.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef CCMATH_LDEXP_HPP
#define CCMATH_LDEXP_HPP

#include <cmath>
#include <limits>
#include <type_traits>
#include <stdexcept>

#include "abs.hpp"
#include "isinf.hpp"
#include "isnan.hpp"

namespace ccmath {

namespace detail {

template <typename Real>
inline constexpr Real ldexp_impl(Real arg, int exp) noexcept
{
    while(exp > 0)
    {
        arg *= 2;
        --exp;
    }
    while(exp < 0)
    {
        arg /= 2;
        ++exp;
    }

    return arg;
}

} // Namespace detail

template <typename Real, std::enable_if_t<!std::is_integral_v<Real>, bool> = true>
inline constexpr Real ldexp(Real arg, int exp) noexcept
{
    if( std::is_constant_evaluated() )
    {
        return ccmath::abs(arg) == Real(0) ? arg :
               ccmath::isinf(arg) ? arg :
               ccmath::isnan(arg) ? arg :
               ccmath::detail::ldexp_impl(arg, exp);
    }
    else
    {
        using std::ldexp;
        return ldexp(arg, exp);
    }
}

template <typename Z, std::enable_if_t<std::is_integral_v<Z>, bool> = true>
inline constexpr double ldexp(Z arg, int exp) noexcept
{
    return ccmath::ldexp(static_cast<double>(arg), exp);
}

inline constexpr float ldexpf(float arg, int exp) noexcept
{
    return ccmath::ldexp(arg, exp);
}

#ifndef BOOST_MATH_NO_LONG_DOUBLE_MATH_FUNCTIONS
inline constexpr long double ldexpl(long double arg, int exp) noexcept
{
    return ccmath::ldexp(arg, exp);
}
#endif

} // Namespaces

#endif // CCMATH_LDEXP_HPP
