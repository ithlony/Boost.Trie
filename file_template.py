# Copyright 2007 Stjepan Rajko.
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at
# http://www.boost.org/LICENSE_1_0.txt)

import os
import time
import shutil
import sys
import getopt
import re

global template
global log
global options
global results

class Log(object):
    def __init__(self):
        self.__level__ = 0

    def __prefix__(self):
        return '|'*self.__level__

    def __print__(self, string):
        print self.__prefix__() + string

    def message(self, string):
        self.__print__('/-------------------------------------------')
        self.__print__('| ' + string)
        self.__print__('+---')

    def phase(self, string):
        self.message(string)
        self.__level__ += 1

    def end(self):
        self.__level__ -= 1
        
    def line(self, string):
        self.__print__('| ' + string)

    def raw(self, string):
        return raw_input(self.__prefix__() + '| ' + string)


log = Log()

# The Options class holds user-specified options.
class Options(object):

    # initializes the object
    # initializes self.options
    # initializes common regular expressions used for option verification
    def __init__(self):
        
        # initialize self.options
        self.options = dict()
        self.options['ignore']=list()
        self.options['fignore']=list()
        
        # initialize common regular expressions
        self.any = re.compile(r'.*\Z')
        self.boolean = re.compile(r'[yn]\Z')
        self.alnum = re.compile(r'\w+\Z')
        self.alnum_lowercase = re.compile(r'[a-z0-9_]+\Z')


    # raises an exception if the string doesn't match the regular expression
    # returns string
    def verify (self, string, regexp):
        if regexp != None and not regexp.match(string):
            raise NameError, string + ' does not match ' + regexp.pattern
        return string


    # makes the value of the option to be value, or prompts if value==None
    # value is set to the new value of the option and returned
    def make(self, option, value, prompt=None):
        if value==None:
            if (option != None):
                log.message('Enter value for option ' + option + ':')
            else:
                log.message('Enter value: ')
            if prompt==None:
                prompt = option + ': '
            value = log.raw(prompt)

        if option != None:
            self.options[option] = value
        return value


    # returns the value of an option.  the user will be prompted if necessary.
    def get(self, option, regexp=None, default=None, prompt=None):
        if self.options.has_key(option):
            # option has already been set
            return self.verify(self.options[option], regexp)
        return self.verify(self.make(option, default, prompt), regexp)


    # returns the value (True/False) of a boolean option.
    def get_boolean(self, option, default_bool=None, prompt=None):
        if default_bool != None:
            if default_bool:
                default = 'y'
            else:
                default = 'n'
        else:
            default = None
        value = self.get(option, self.boolean, default, prompt)
        return value=='y'


# The Replacement class models a template replacement,
# either for file names or file content.
class Replacement(object):
    def __init__(self, template, value):
        self.template = template
        self.value = value
    def replace(self, string):
        return string.replace(self.template, self.value)


# Replacements is a collection of Replacement objects.
class Replacements(list):
    def replace(self, string):
        for item in self:
            string = item.replace(string)
        return string


# FileSpecificReplacement associates file extensions with a replacement   
class FileSpecificReplacement(Replacement):
    def __init__(self, extensions, key, value):
        Replacement.__init__(self, key, value)
        self.process_extensions = extensions

    def matches(self, name):
        for item in self.process_extensions:
            if name.endswith(item):
                return True
        return False
        
    def replace(self, name, string):
        if self.matches(name):
            return string.replace(self.template, self.value)
        return string
    
    def __str__(self):
        return str(self.process_extensions) + ':' + self.template + '->' + self.value


class FileSpecificReplacements(Replacements):
    def matches(self, name):
        for item in self:
            if item.matches(name):
                return True
        return False

# ContentReplacements contains both templates for specific file extensions
# and all processable file extensions.
class ContentReplacements:
    def __init__(self):
        self.general_replacements = Replacements()
        self.specific_replacements = FileSpecificReplacements()

    def replace(self, name, content):
        # check to see if we should process this file
        if not self.matches(name):
            return content
        for item in self.specific_replacements:
            content = item.replace(name, content)
        for item in self.general_replacements:
            content = item.replace(content)
        return content
        
    def matches(self, name):
        match = False
        for item in self.specific_replacements:
            if item.matches(name):
                match = True
                break
        return match

# The Template class holds information about a template,
# such as all of its options and replacements.
class Template(object):
    def __init__(self):
        self.__file_list__ = list()
        self.__directory_list__ = list()
        self.__python_list__ = list()

        self.template_dir = ''
        self.options = Options()
        self.content_replacements = ContentReplacements()
        self.name_replacements = Replacements()

    def read_content(self, file_name):
        fin = open(file_name, "r")
        content = fin.read()
        fin.close()
        return content

    def submit_content(self, content):
        self.__content__ = content

    def append_content(self, content):
        self.__content__ += content

    def process_content(self, name, python=False):
        file_name = os.path.join(self.directory, name)
        if python:
            self.__content__ = ''
            global template
            template = self
            self.executing = file_name
            execfile(file_name + '.py')
            content = self.__content__
        else:
            if not self.content_replacements.matches(name):
                return None
            content = self.read_content(file_name)

        # only take the content from first $template_start$ on,
        # and convert all line breaks to '\n'
        beginning = content.find('$template_start$')
        if beginning >= 0:
            content = content[beginning:len(content)]
        
        content_lines = content.splitlines()
        if beginning >= 0:
            content_lines.pop(0)
        content = '\n'.join(content_lines) + '\n'

        return self.replace_content(name, content)

    def name_replacement(self, key, value):
        self.name_replacements.append(Replacement(key, value))

    def general_content_replacement(self, key, value):                    
        self.content_replacements.general_replacements.append(Replacement(key, value))

    def content_replacement(self, extensions, key, value):
        self.content_replacements.specific_replacements.append(
            FileSpecificReplacement(extensions, key, value))

    def replace_name(self, name):
        return self.name_replacements.replace(name)

    def replace_content(self, name, content):
        return self.content_replacements.replace(name, content)

    def ignore(self, name):
        self.options.options['ignore'].append(os.path.normpath(name))

    def examine(self):
        self.directory = self.options.get('template')
        self.into = self.options.get('into',None,'')
        ignore_list = self.options.get('ignore')
        fignore_list = self.options.get('fignore')
        
        cwd = os.getcwd()
        os.chdir(self.directory)
        for root, dirs, files in os.walk('.'):
            # strip the . from the root
            rest = list()
            rest_of_root = root
            while rest_of_root != '.':
                rest.insert(0, os.path.basename(rest_of_root))
                rest_of_root = os.path.dirname(rest_of_root)
            root = ''
            for item in rest:
                root = os.path.join(root, item)
            log.line(root)

            self.__dirs_clear__ = list()
            self.__files_clear__ = list()

            for name in files:
                if name.startswith('.') or ignore_list.count(os.path.normpath(os.path.join(root, name)))>0:
                    continue
                fignored=False
                for item in fignore_list:
                    if name.endswith(item) or name.endswith(item+'.py'):
                        fignored=True
                        break
                if fignored:
                    continue

                pathname = (os.path.join(root, name))
                if name.endswith('.py'):
                    content = self.read_content(os.path.join(root, name))

                    if content.startswith('# template script'):
                        execfile(pathname)
                    elif content.startswith('# template file'):
                        self.__python_list__.append(pathname[0:len(pathname)-3])
                    else:
                        self.__file_list__.append(pathname)
                else:
                    self.__file_list__.append(pathname)

            for name in self.__files_clear__:
                self.__file_list__.remove(os.path.join(root, name))

            for name in dirs:
                if name.startswith('.') or \
                   ignore_list.count(os.path.normpath(os.path.join(root, name)))>0:
                    self.ignore_subdirectory(name)
            for name in self.__dirs_clear__:
                dirs.remove(name)
            for name in dirs:
                self.__directory_list__.append( (os.path.join(root, name)) )

        os.chdir(cwd)
        return self.__directory_list__, self.__file_list__, self.__python_list__

    def ignore_subdirectory(self, name):
        self.__dirs_clear__.append(name)

    def ignore_subfile(self, name):
        self.__files_clear__.append(name)

    def __append_resulting__(self, resulting_list, item_list, prefix):
        for name in item_list:
            if name.startswith(prefix):
                resulting_list.append(item)
        return resulting_list

    def resulting_directory_list(prefix):
        new_prefix = self.replace_name(prefix)
        result = list()
        return self.__append_resulting__(result, self.__directory_list__, new_prefix)

    def resulting_file_list(prefix):
        new_prefix = self.replace_name(prefix)
        result = list()
        self.__append_resulting__(result, self.__file_list__, new_prefix)
        return self.__append_resulting(result, self.__python_list__, new_prefix)

def set_content(name, content):
    fout = open(name, "w")
    fout.write(content)
    fout.close()

class Result(object):
    def __init__(self, template, source, destination):
        self.template = template
        self.source = source
        self.destination = destination
    def __str__(self):
        return str((self.template.options.get('template'), self.source, self.destination))

class Results(object):
    def __init__(self):
        self.directory_list = list()
        self.file_list = list()
        self.python_list = list()

    def append(self, template, directory_list, file_list, python_list):
        self.__append_list__(self.directory_list, template, directory_list)
        self.__append_list__(self.file_list, template, file_list)
        self.__append_list__(self.python_list, template, python_list)

    def __append_list__(self, my_list, template, append_list):
        for item in append_list:
            result = Result(template, item, os.path.join(template.into,template.replace_name(item)))
            my_list.append(result)

    def __mkdir__(self,directory):
        parent = os.path.dirname(directory)
        if len(parent) and not os.path.exists(parent):
            self.__mkdir__(parent)
        os.mkdir(directory)

    def prepare(self):
        self.destination = options.get('destination', None, '.')
        if not os.path.exists(self.destination):
            self.__mkdir__(self.destination)

        log.message('Directories:')
        for item in self.directory_list:
            log.line(item.destination)
            self.erase(item.destination)
        for item in self.directory_list:
            path = os.path.join(self.destination, item.destination)
            if not os.path.exists(path):
                self.__mkdir__(path)

        log.message('Files:')
        for item in self.file_list + self.python_list:
            log.line(item.destination)
            self.erase(item.destination)

    def erase(self, name):
        path = os.path.join(self.destination, name)       
        if os.path.exists(path):
            log.message(path + ' already exists.')
            do_erase = options.get_boolean(
                None, None, 'Erase ' + path + '? [y/n] ')
            if do_erase:
                if os.path.isfile(path):
                    os.remove(path)
                if os.path.isdir(path):
                        log.phase('Erasing...')
                        for root, dirs, files in os.walk(path, topdown=False):
                            for name in files:
                                log.line(os.path.join(root, name))
                                os.remove(os.path.join(root, name))
                            for name in dirs:
                                log.line(os.path.join(root, name))
                                os.rmdir(os.path.join(root, name))
                        log.line(path)
                        os.rmdir(path)
                        log.end()

    def create(self):
        log.phase('Python files...')
        for item in self.python_list:
            new_name = os.path.join(self.destination, item.destination)
            log.line(new_name)
            content = item.template.process_content(item.source, True)
            set_content(new_name, content)
        log.end()

        log.phase('Files...')
        for item in self.file_list:
            template = item.template
            new_name = os.path.join(self.destination, item.destination)
            log.line(new_name)
            content = item.template.process_content(item.source)
            if content:
                set_content(new_name, content)
            else:
                shutil.copy(os.path.join(item.template.directory, item.source), new_name)
        log.end()

    def __scan__(self, my_list, directory):
        result_list = list()
        for item in my_list:
            idir, ibase = os.path.split(item.destination)
            if os.path.normpath(idir) == os.path.normpath(directory) and result_list.count(ibase)==0:
                result_list.append(ibase)
        return result_list

    def files_in(self, directory):
        return self.__scan__(self.file_list + self.python_list, directory)

#    def file_contents_in(self, directory):
#        files = self.__scan__(self.file_list + self.python_list, directory)
        

    def directories_in(self, directory):
        return self.__scan__(self.directory_list, directory)
    
    def walk(self, base, directory):
        # get all files and subdirectories        
        root = os.path.normpath(directory)
        dirs = self.directories_in(os.path.join(base, directory))
        files = self.files_in(os.path.join(base, directory))
        yield root, files, dirs
        for d in dirs:
            for root, files, dirs in self.walk(base, os.path.join(directory, d)):
                yield root, files, dirs

# reads options from the command line
# command line has the format:
# python make_template.py (option=value)* ((template) (option=value)*)* 
# options specified immediately after a template are for that template only.
# options specified at the beginning are for all templates.
def process_command_line():  
    templates = list()
    templates.append(Template())
    index = 0

    global_options = ['destination']    
    options = templates[0].options
    
    for arg in sys.argv[1:]:
        split = arg.split('=')
        option = split[0]
        val = '='.join(split[1:len(split)])
        if len(split)==1:
            # templates can be specified without template=
            val = option
            option = 'template'

        # option=value sets the option
        if option=='template':
            # done with this template, move to the next
            templates.append(Template())
            index += 1
        if global_options.count(option)>0:
            options.options[option] = val
        elif option == 'ignore':
            templates[index].ignore(val)
        elif option == 'fignore':
            templates[index].options.options[option].append(val)
        else:
            templates[index].options.options[option] = val

    templates.pop(0)

    if not len(templates):
        # user never specified a template
        templates.append(Template())
        templates[0].options.get('template')
    else:
        # last set of options applies to all templates
        for t in templates[1:]:
            for option,value in options.options.iteritems():
                if not t.options.options.has_key(option):
                    t.options.options[option] = value

    return templates, options

# The main processing script.

templates, options = process_command_line()
results = Results()

# template is a global variable accessible by template scripts.
for template in templates:

    # We first read the template script file and run it.
    template_path = template.options.get('template')
    log.phase('Processing template ' + template_path + ' with options:')
    log.line(str(template.options.options))

    # We then traverse the template tree and prepare a list of
    # directories and files to be created, and process any found template
    # scripts.
    log.phase('Examining the template project tree...')
    directory_list, file_list, python_list = template.examine()
    results.append(template, directory_list, file_list, python_list)
    
    log.end()
 
    log.end()

# prepare the destination tree by erasing existing files and directories.
log.phase('Preparing destination tree...')
results.prepare()
log.end()

log.phase('Creating file tree from template...')
results.create()
log.end()
