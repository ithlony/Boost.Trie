# Copyright 2007 Stjepan Rajko.
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at
# http://www.boost.org/LICENSE_1_0.txt)

current=`pwd`
cd results/sandbox_command_line/my_library/libs/my_library/doc
bjam $*
cd ../example
bjam $*
cd ../test
bjam $*

cd $current
