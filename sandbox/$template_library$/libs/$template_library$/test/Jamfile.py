# template file

# Copyright 2007 Stjepan Rajko.
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at
# http://www.boost.org/LICENSE_1_0.txt)

template.append_content("""$template_copyright$

import testing ;

project
    : requirements 
      <include>../../..
      <define>BOOST_ALL_NO_LIB=1
    ;

""")

for item in results.files_in(template.replace_name(
    '$template_library$/libs/$template_library$/test')):
    if item.endswith('.cpp'):
        template.append_content('run ' + item + ' ;\n')
