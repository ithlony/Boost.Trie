# Copyright 2007 Stjepan Rajko.
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at
# http://www.boost.org/LICENSE_1_0.txt)

import os.path
import sys
import StringIO
import os
import filecmp
import difflib
import re

global test_results

def compare(a, b):
    global test_results
    dircmp = filecmp.dircmp(a, b, ['RCS', 'CVS', 'tags', '.svn', '.DS_Store'])
    if len(dircmp.diff_files) or len(dircmp.left_only) or len(dircmp.right_only):
        test_results += '...comparing ' + a + ' and ' + b + '...\n'
    for item in dircmp.diff_files:
        test_results += 'Differing file ' + item + '\n'
        linesa = open(os.path.join(a, item), "rbU").readlines()
        linesb = open(os.path.join(b, item), "rbU").readlines()

        id = re.compile(' [a-fA-F0-9]{24} ')
        if item == 'project.pbxproj':
            test_results +=  'Compensating for UUID differences.\n'
            for i in range(0,len(linesa)):
                linesa[i] = re.sub(id, ' UUIDUUIDUUIDUUIDUUIDUUID ', linesa[i])
            for i in range(0,len(linesb)):
                linesb[i] = re.sub(id, ' UUIDUUIDUUIDUUIDUUIDUUID ', linesb[i])
        id = re.compile(r'\{([a-fA-F0-9]){8}\-[a-fA-F0-9]{4}\-[a-fA-F0-9]{4}\-[a-fA-F0-9]{4}\-[a-fA-F0-9]{12}\}')
        if item.endswith('.vcproj') or item.endswith('.sln'):
            test_results +=  'Compensating for UUID differences.\n'
            for i in range(0,len(linesa)):
                linesa[i] = re.sub(id, '{UUIDUUIDUUIDUUIDUUIDUUID}', linesa[i])
            for i in range(0,len(linesb)):
                linesb[i] = re.sub(id, '{UUIDUUIDUUIDUUIDUUIDUUID}', linesb[i])

        for line in difflib.unified_diff(linesb, linesa):
            test_results += line
    if len(dircmp.left_only):
        test_results += 'Extra: ' + str(dircmp.left_only) + '\n'
    if len(dircmp.right_only):
        test_results += 'Missing: ' + str(dircmp.right_only) + '\n'
    for item in dircmp.common_dirs:
        compare(os.path.join(a, item), os.path.join(b, item))

def run_test (result, expected, input, arguments):

    result=os.path.join('results', result)
    expected=os.path.join('expected', expected)
    
    sys.stdin = StringIO.StringIO(input)
    sys.argv = ['file_template.py', 'destination=' + result] + arguments

    global test_results
    test_results += '----------------\n'
    test_results += 'input | file_template.py ' + str(arguments) + '\n'
    test_results += '----------------\n'
    
    path = os.path.abspath('../../../..')
    sys_path = list(sys.path)
    sys.path.append(path)
    if sys.modules.has_key('file_template'):
        del(sys.modules['file_template'])
    __import__('file_template', globals(), dict())
    sys.path = sys_path

    compare (result, expected)

print 'Erasing test.results...'
if os.path.exists('test.results'):
    os.remove('test.results')

for root, dirs, files in os.walk('results', topdown=False):
    for name in files:
        os.remove(os.path.join(root, name))
    for name in dirs:
        print os.path.join(root, name)
        os.rmdir(os.path.join(root, name))

test_results = ''

run_test('simple_type_in',  'simple_template', 'substituted\n', ['simple_template'])
run_test('simple_command_line', 'simple_template', '', ['simple_template', 'text=substituted'])
run_test('simple_ignore', 'simple_template_ignored', '', ['simple_template', 'text=substituted', 'ignore=$template_text$'])
run_test('simple_fignore', 'simple_template_fignored', '', ['simple_template', 'text=substituted', 'fignore=.txt'])
run_test('sandbox_command_line', 'sandbox_command_line', '', ['../../../../sandbox', 'authors=John Doe', 'library=my_library'])
run_test('sandbox_global_htmlfiles', 'sandbox_global_htmlfiles', '', ['../../../../sandbox', 'authors=John Doe,Jane H. Dough', 'library=my_library', 'htmlfiles=global'])
run_test('sandbox_ide', 'sandbox_ide', '', ['../../../../sandbox', 'authors=John Doe,Jane H. Dough,Jan De_Man', 'library=my_library', 'vc8ide=y', 'xcodeide=y'])

print
print
print
print '--------------------------------------------------------'
print '- Final test.results diff:'

print test_results