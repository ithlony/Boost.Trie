# template script

# Copyright 2007 Stjepan Rajko.
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at
# http://www.boost.org/LICENSE_1_0.txt)

docs = template.options.get('docs')
htmlfiles = template.options.get('htmlfiles', None, 'local')

if docs != 'qb+doxy':
    template.ignore_subdirectory('dox')

if htmlfiles!='local':
    template.ignore('$template_library$/libs/$template_library$/doc/html/images')
