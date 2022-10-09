//  (C) Copyright Matt Borland 2021.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_ISNORMAL_HPP
#define BOOST_MATH_ISNORMAL_HPP

#include <cmath>
#include <limits>
#include <type_traits>

#include "abs.hpp"
#include "isinf.hpp"
#include "isnan.hpp"

namespace ccmath {

template <typename T>
inline constexpr bool isnormal(T x)
{
    if( std::is_constant_evaluated() )
    {
        return x == T(0) ? false :
               ccmath::isinf(x) ? false :
               ccmath::isnan(x) ? false :
               ccmath::abs(x) < (std::numeric_limits<T>::min)() ? false : true;
    }
    else
    {
        using std::isnormal;

        if constexpr (!std::is_integral_v<T>)
        {
            return isnormal(x);
        }
        else
        {
            return isnormal(static_cast<double>(x));
        }
    }
}
}

#endif // BOOST_MATH_ISNORMAL_HPP
