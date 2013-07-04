# template file

# Copyright 2007 Stjepan Rajko.
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at
# http://www.boost.org/LICENSE_1_0.txt)

docs = template.options.get('docs')
doxygen = docs != 'qb'
htmlfiles = template.options.get('htmlfiles', None, 'local')

template.append_content("""$template_start$
$template_copyright$

project boost/$template_library$/doc ;

import boostbook : boostbook ;
using quickbook ;

local loc = [ path.native [ path.pwd ] ] ;
local root = [ path.native [ path.join [ path.pwd ] ../../.. ] ] ;

xml $template_library$_xml : $template_library$.qbk ;""")

doxy_source_files = list()
for root, dirs, files in results.walk(
    # we want the returned root to be relative to $template_library$
    template.replace_name('$template_library$'),
    # and want to walk the boost/$template_library$ directory underneath that
    template.replace_name('boost/$template_library$')):
    if os.path.basename(root) != 'detail':
        doxy_source_files.append(
            template.replace_name(os.path.join(os.path.join('../../..',
            root), '*.hpp').replace('\\','/')))

if doxygen:
    template.append_content("""
doxygen $template_library$_doxygen
   :
      [ glob
             """ + """
             """.join(doxy_source_files) + """ ]
   :
        <doxygen:param>EXAMPLE_PATH=../example
        <doxygen:param>STRIP_FROM_PATH=$(root)
        <doxygen:param>STRIP_FROM_INC_PATH=$(root)
        <doxygen:param>EXTRACT_ALL=NO
        <doxygen:param>HIDE_UNDOC_MEMBERS=NO
        <doxygen:param>EXTRACT_PRIVATE=NO
        <doxygen:param>DETAILS_AT_TOP=YES
        <doxygen:param>ENABLE_PREPROCESSING=YES
        <doxygen:param>MACRO_EXPANSION=YES
        <doxygen:param>SEARCH_INCLUDES=YES
        <doxygen:param>INCLUDE_PATH=../../..
        <doxygen:param>PREDEFINED=DOXYGEN_DOCS_ONLY""")

    template.append_content("""
   ;
""")

template.append_content("""
boostbook standalone
   :
      $template_library$_xml""")
if (doxygen):
    template.append_content("""
      $template_library$_doxygen""")

template.append_content("""
    :
        # pull in the online .css and images
        <xsl:param>project.root=http://beta.boost.org/development
        # without the next line, build complains
        <xsl:param>annotation.support=1
        # pulled this from the doc_test Jamfile
        <xsl:param>quickbook.source.style.show="'true'"

        <xsl:param>chunk.first.sections=1
        <xsl:param>chunk.section.depth=3
        <xsl:param>toc.section.depth=3
        <xsl:param>toc.max.depth=3
        <xsl:param>generate.section.toc.level=3
""")

template.append_content(
"""    ;
""")

