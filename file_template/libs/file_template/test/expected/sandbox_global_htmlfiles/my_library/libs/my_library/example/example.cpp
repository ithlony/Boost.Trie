// Copyright 2007 John Doe and Jane H. Dough.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


//[ my_library_example

#include <boost/my_library.hpp>
#include <boost/assert.hpp>

void my_library_example()
{
    boost::my_library::my_library<int> object;
    int x = 0;

    BOOST_ASSERT(object.get_nothing_count()==0);
    object.nothing(x);
    BOOST_ASSERT(object.get_nothing_count()==1);

    BOOST_ASSERT(object.get_call_count()==1);
    object.nothing(x,4);
    BOOST_ASSERT(object.get_call_count()==2);
    BOOST_ASSERT(object.get_nothing_count()==5);

} // end void my_library_example

int main()
{
    my_library_example();
}
//]
