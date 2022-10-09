//  (C) Copyright Matt Borland 2021.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef CCMATH_TRUNC_HPP
#define CCMATH_TRUNC_HPP

#include <cmath>
#include <type_traits>

#include "abs.hpp"
#include "isinf.hpp"
#include "isnan.hpp"
#include "floor.hpp"
#include "ceil.hpp"

namespace ccmath {

namespace detail {

template <typename T>
inline constexpr T trunc_impl(T arg) noexcept
{
    return (arg > 0) ? ccmath::floor(arg) : ccmath::ceil(arg);
}

} // Namespace detail

template <typename Real, std::enable_if_t<!std::is_integral_v<Real>, bool> = true>
inline constexpr Real trunc(Real arg) noexcept
{
    if( std::is_constant_evaluated() )
    {
        return ccmath::abs(arg) == Real(0) ? arg :
               ccmath::isinf(arg) ? arg :
               ccmath::isnan(arg) ? arg :
               ccmath::detail::trunc_impl(arg);
    }
    else
    {
        using std::trunc;
        return trunc(arg);
    }
}

template <typename Z, std::enable_if_t<std::is_integral_v<Z>, bool> = true>
inline constexpr double trunc(Z arg) noexcept
{
    return ccmath::trunc(static_cast<double>(arg));
}

inline constexpr float truncf(float arg) noexcept
{
    return ccmath::trunc(arg);
}

#ifndef BOOST_MATH_NO_LONG_DOUBLE_MATH_FUNCTIONS
inline constexpr long double truncl(long double arg) noexcept
{
    return ccmath::trunc(arg);
}
#endif

} // Namespaces

#endif // CCMATH_TRUNC_HPP
