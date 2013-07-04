// Copyright 2007 Stjepan Rajko.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

$template_start$
$template_copyright$

//[ $template_library$_example

#include <boost/$template_library$.hpp>
#include <boost/assert.hpp>

void $template_library$_example()
{
    boost::$template_library$::$template_library$<int> object;
    int x = 0;

    BOOST_ASSERT(object.get_nothing_count()==0);
    object.nothing(x);
    BOOST_ASSERT(object.get_nothing_count()==1);

    BOOST_ASSERT(object.get_call_count()==1);
    object.nothing(x,4);
    BOOST_ASSERT(object.get_call_count()==2);
    BOOST_ASSERT(object.get_nothing_count()==5);

} // end void $template_library$_example

int main()
{
    $template_library$_example();
}
//]