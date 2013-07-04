# template script

# Copyright 2007 Stjepan Rajko.
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at
# http://www.boost.org/LICENSE_1_0.txt)

text = template.options.get('text', template.options.alnum_lowercase, None, '(type in "substituted"): ')

template.name_replacement('$template_text$', text)

template.general_content_replacement('$template_substitution$', 'substituted')
template.content_replacement(['.txt'], '$template_text$', text + ' in txt file')
template.content_replacement(['.xyz'], '$template_text$', text + ' in xyz file')
