# template script

if template.options.get_boolean('xcodeide', False):

    log.message('Processing Xcode IDE template.')
    template.ignore('$template_library$/libs/$template_library$/build/xcodeide/$template_library$.xcodeproj/xcode_elements.py')
    template.ignore('$template_library$/libs/$template_library$/build/xcodeide/$template_library$.xcodeproj/xcode_elements.pyc')
    
else:

    template.ignore_subdirectory('xcodeide')
