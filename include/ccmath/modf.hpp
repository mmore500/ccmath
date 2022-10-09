//  (C) Copyright Matt Borland 2021.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef CCMATH_MODF_HPP
#define CCMATH_MODF_HPP

#include <cmath>
#include <limits>
#include <type_traits>

#include "abs.hpp"
#include "isinf.hpp"
#include "isnan.hpp"
#include "trunc.hpp"

namespace ccmath {

namespace detail {

template <typename Real>
inline constexpr Real modf_error_impl(Real x, Real* iptr)
{
    *iptr = x;
    return ccmath::abs(x) == Real(0) ? x :
           x > Real(0) ? Real(0) : -Real(0);
}

template <typename Real>
inline constexpr Real modf_nan_impl(Real x, Real* iptr)
{
    *iptr = x;
    return x;
}

template <typename Real>
inline constexpr Real modf_impl(Real x, Real* iptr)
{
    *iptr = ccmath::trunc(x);
    return (x - *iptr);
}

} // Namespace detail

template <typename Real>
inline constexpr Real modf(Real x, Real* iptr)
{
    if( std::is_constant_evaluated() )
    {
        return ccmath::abs(x) == Real(0) ? detail::modf_error_impl(x, iptr) :
               ccmath::isinf(x) ? detail::modf_error_impl(x, iptr) :
               ccmath::isnan(x) ? detail::modf_nan_impl(x, iptr) :
               ccmath::detail::modf_impl(x, iptr);
    }
    else
    {
        using std::modf;
        return modf(x, iptr);
    }
}

inline constexpr float modff(float x, float* iptr)
{
    return ccmath::modf(x, iptr);
}

#ifndef BOOST_MATH_NO_LONG_DOUBLE_MATH_FUNCTIONS
inline constexpr long double modfl(long double x, long double* iptr)
{
    return ccmath::modf(x, iptr);
}
#endif

} // Namespaces

#endif // CCMATH_MODF_HPP
