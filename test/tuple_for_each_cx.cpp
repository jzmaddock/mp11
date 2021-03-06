
//  Copyright 2015 Peter Dimov.
//
// Distributed under the Boost Software License, Version 1.0.
//
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt

#include <boost/mp11/tuple_for_each.hpp>
#include <boost/config.hpp>

// Technically std::tuple isn't constexpr enabled in C++11, but it works with libstdc++

#if defined( BOOST_NO_CXX11_CONSTEXPR ) || ( defined( _LIBCPP_VERSION ) && __cplusplus < 201400L )

int main() {}

#else

#include <tuple>
#include <type_traits>

struct assert_is_integral
{
    template<class T> constexpr bool operator()( T ) const
    {
        static_assert( std::is_integral<T>::value, "T must be an integral type" );
        return true;
    }
};

int main()
{
    {
        constexpr std::tuple<int, short, char> tp{ 1, 2, 3 };
        constexpr auto r = boost::mp11::tuple_for_each( tp, assert_is_integral() );
        (void)r;
    }

#if defined( __clang_major__ ) && __clang_major__ == 3 && __clang_minor__ < 9
#else

    {
        constexpr std::tuple<> tp;
        constexpr auto r = boost::mp11::tuple_for_each( tp, 11 );
        static_assert( r == 11, "r == 11" );
    }

#endif
}

#endif
