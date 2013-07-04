// Copyright 2007 Stjepan Rajko.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

$template_start$
$template_copyright$

#include <boost/$template_library$.hpp>

#include <boost/test/included/test_exec_monitor.hpp>

int test_main(int, char* [])
{
    boost::$template_library$::$template_library$<int> object;
    int x = 0;
    BOOST_CHECK_EQUAL(object.get_call_count(),0);
    object.nothing(x,4);
    BOOST_CHECK_EQUAL(object.get_call_count(),1);
    BOOST_CHECK_EQUAL(object.get_nothing_count(),4);
    
    return 0;
};
