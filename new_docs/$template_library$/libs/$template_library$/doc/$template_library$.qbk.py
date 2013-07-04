# template file

# Copyright 2007 Stjepan Rajko.
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at
# http://www.boost.org/LICENSE_1_0.txt)

docs = template.options.get('docs')
                     
template.append_content("""
[article $template_Library$
    [quickbook 1.4]
    [version 0.01e-10]
    [authors $template_authors_reversed$]
    [copyright $template_year$ $template_authors$]
    [purpose Doing nothing.]
    [license
        Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
        [@http://www.boost.org/LICENSE_1_0.txt])
    ]
]

Welcome to the $template_Library$!  One day, it will perhaps be called
$template_Boost_Library$. Until then, feel free to use it to do nothing.

[warning $template_Library$ is not an official Boost library.]

[section:introduction Introduction]

User, this is $template_Library$.  $template_Library$, this is the user.  Be nice to each other.

[section:start Getting Started]

The $template_Library$ is located in the $template_library$ directory of the boost sandbox.

""")
if docs!='qb':
    template.append_content("""
You might also want to look at the [link $template_library$.reference reference].

""")

template.append_content("""
[endsect]

[endsect]
""")
if docs=='qb+doxy':
    template.append_content("""
[section:reference Reference]

The reference for this library is [@doxygen/index.html generated separately].

[endsect]

""")
elif docs=='qb+doxyref':
    template.append_content("""
[xinclude $template_library$_doxygen.xml]
""")

template.append_content("""
[section:license License]

$template_qbk_copyright$

[endsect]
""")

