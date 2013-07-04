# template script

# Copyright 2007 Stjepan Rajko.
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at
# http://www.boost.org/LICENSE_1_0.txt)

log.message('Welcome to the Boost Sandbox template - the IBD version.')

library_name = template.options.get('library', template.options.alnum_lowercase, None,
    '(all lowercase, use underscores to separate words, e.g. "my_library"): ')

library_name_list = library_name.split("_")
library_name_list_capitalized = list()
for item in library_name_list[:]:
    library_name_list_capitalized.append(item.capitalize())
library_name_capitalized = ' '.join(library_name_list_capitalized)
library_name_concat_capitalized = ''.join(library_name_list_capitalized)

_copyright = """_COMMENT_Copyright $template_year$ $template_authors$.
_COMMENT_Distributed under the Boost Software License, Version 1.0. (See
_COMMENT_accompanying file LICENSE_1_0.txt or copy at
_COMMENT_http://www.boost.org/LICENSE_1_0.txt)
"""

author_list = template.options.get('authors', template.options.any, None,
    '(comma separated, no spaces outside names, e.g., "My Name,Notmy R. Name": ')
author_list = author_list.split(',')
authors_reversed = list()
for name in author_list:
    names = name.split(" ")
    first = names[0:len(names)-1]
    last = names[len(names)-1].split('_')
    authors_reversed.append('[' + ' '.join(last) + ', ' + ' '.join(first) + ']')

if len(author_list) > 1:
    author_list = (','.join(author_list[0:len(author_list)-1]) +
                   " and " + author_list[len(author_list)-1]).replace(',', ', ')
else:
    author_list = author_list[0]
    
author_list = author_list.replace('_',' ')

template.name_replacement('$template_library$', library_name)

template.general_content_replacement('$template_library$', library_name)
template.general_content_replacement('$template_Library$', library_name_capitalized)
template.general_content_replacement('$template_LibraryConcat$', library_name_concat_capitalized)
template.general_content_replacement('$template_LIBRARY$', library_name.upper())
template.general_content_replacement('$template_Boost_Library$', 'Boost.' + library_name_capitalized)
template.content_replacement(['.v2', '.jam', 'Jamfile', '.qbk', '.py'], '$template_copyright$', _copyright.replace('_COMMENT_','# '))
template.content_replacement(['.hpp', '.cpp'], '$template_copyright$', _copyright.replace('_COMMENT_','// '))
template.content_replacement(['.qbk'], '$template_qbk_copyright$',(_copyright.replace('_COMMENT_',''))
                             .replace('http://www.boost.org/LICENSE_1_0.txt',
                                      '[@http://www.boost.org/LICENSE_1_0.txt]'))
template.general_content_replacement('$template_authors_reversed$', ','.join(authors_reversed))
template.general_content_replacement('$template_authors$', author_list)
template.general_content_replacement('$template_year$', str(time.localtime().tm_year))

