//  (C) Copyright Matt Borland 2021.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef CCMATH_CEIL_HPP
#define CCMATH_CEIL_HPP

#include <cmath>
#include <type_traits>

#include "floor.hpp"
#include "abs.hpp"
#include "isinf.hpp"
#include "isnan.hpp"

namespace ccmath {

namespace detail {

template <typename T>
inline constexpr T ceil_impl(T arg) noexcept
{
    T result = ccmath::floor(arg);

    if(result == arg)
    {
        return result;
    }
    else
    {
        return result + 1;
    }
}

} // Namespace detail

template <typename Real, std::enable_if_t<!std::is_integral_v<Real>, bool> = true>
inline constexpr Real ceil(Real arg) noexcept
{
    if(std::is_constant_evaluated())
    {
        return ccmath::abs(arg) == Real(0) ? arg :
               ccmath::isinf(arg) ? arg :
               ccmath::isnan(arg) ? arg :
               ccmath::detail::ceil_impl(arg);
    }
    else
    {
        using std::ceil;
        return ceil(arg);
    }
}

template <typename Z, std::enable_if_t<std::is_integral_v<Z>, bool> = true>
inline constexpr double ceil(Z arg) noexcept
{
    return ccmath::ceil(static_cast<double>(arg));
}

inline constexpr float ceilf(float arg) noexcept
{
    return ccmath::ceil(arg);
}

#ifndef BOOST_MATH_NO_LONG_DOUBLE_MATH_FUNCTIONS
inline constexpr long double ceill(long double arg) noexcept
{
    return ccmath::ceil(arg);
}
#endif

} // Namespaces

#endif // CCMATH_CEIL_HPP
