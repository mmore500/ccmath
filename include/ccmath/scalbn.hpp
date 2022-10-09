//  (C) Copyright Matt Borland 2021.
//  (C) Copyright John Maddock 2021.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef CCMATH_SCALBN_HPP
#define CCMATH_SCALBN_HPP

#include <cmath>
#include <cfloat>
#include <limits>
#include <type_traits>

#include "abs.hpp"
#include "isinf.hpp"
#include "isnan.hpp"

namespace ccmath {

namespace detail {

template <typename Real, typename Z>
inline constexpr Real scalbn_impl(Real arg, Z exp) noexcept
{
    while(exp > 0)
    {
        arg *= FLT_RADIX;
        --exp;
    }
    while(exp < 0)
    {
        arg /= FLT_RADIX;
        ++exp;
    }

    return arg;
}

} // Namespace detail

template <typename Real, std::enable_if_t<!std::is_integral_v<Real>, bool> = true>
inline constexpr Real scalbn(Real arg, int exp) noexcept
{
    if( std::is_constant_evaluated() )
    {
        return ccmath::abs(arg) == Real(0) ? arg :
               ccmath::isinf(arg) ? arg :
               ccmath::isnan(arg) ? arg :
               ccmath::detail::scalbn_impl(arg, exp);
    }
    else
    {
        using std::scalbn;
        return scalbn(arg, exp);
    }
}

template <typename Z, std::enable_if_t<std::is_integral_v<Z>, bool> = true>
inline constexpr double scalbn(Z arg, int exp) noexcept
{
    return ccmath::scalbn(static_cast<double>(arg), exp);
}

inline constexpr float scalbnf(float arg, int exp) noexcept
{
    return ccmath::scalbn(arg, exp);
}

#ifndef BOOST_MATH_NO_LONG_DOUBLE_MATH_FUNCTIONS
inline constexpr long double scalbnl(long double arg, int exp) noexcept
{
    return ccmath::scalbn(arg, exp);
}
#endif

} // Namespaces

#endif // CCMATH_SCALBN_HPP
