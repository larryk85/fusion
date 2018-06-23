/*=============================================================================
    Copyright (c) 2018 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/config.hpp>
#include <boost/core/lightweight_test.hpp>

namespace aux_
{

// Compilers are able to elide copy ctor, so use dtor for counting object instead.
struct copy_counter
{
    BOOST_DEFAULTED_FUNCTION(copy_counter(), {})
    BOOST_DEFAULTED_FUNCTION(copy_counter(copy_counter const&), {})
    BOOST_DEFAULTED_FUNCTION(copy_counter& operator=(copy_counter const&), { return *this; })

    static int& value()
    {
        static int value = 0;
        return value;
    }

    ~copy_counter()
    {
        ++value();
    }

    static void check(int expected)
    {
#if !BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1910))
        BOOST_TEST_EQ(value(), expected);
#endif
    }
};

}
