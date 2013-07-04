# template file

import uuid

sys_path = list(sys.path)
print os.path.abspath(os.path.dirname(template.executing))
sys.path.append(os.path.abspath(os.path.dirname(template.executing)))
import xcode_elements
sys.path = sys_path

uuid_project = uuid.uuid4().get_hex()[0:24]
uuid_project_buildConfigurationList = uuid.uuid4().get_hex()[0:24]
uuid_project_buildPhase_debug = uuid.uuid4().get_hex()[0:24]
uuid_project_buildPhase_release = uuid.uuid4().get_hex()[0:24]

targets = [xcode_elements.Doc(), xcode_elements.DocClean(),
    xcode_elements.Build('example'), xcode_elements.Clean('example'),
    xcode_elements.Build('test'), xcode_elements.Clean('test') ]

template.append_content(
"""// !$*UTF8*$!
{
    archiveVersion = 1;
    classes = {
    };
    objectVersion = 42;
    objects = {
/* Begin PBXAggregateTarget section */""")

for item in targets:
    template.append_content(item.PBXAggregateTarget())
template.append_content("""
/* End PBXAggregateTarget section */

/* Begin PBXProject section */
        """ + uuid_project + """ /* Project object */ = {
            isa = PBXProject;
            buildConfigurationList = """ + uuid_project_buildConfigurationList + """ /* Build configuration list for PBXProject "$template_library$" */;
            hasScannedForEncodings = 0;
            projectDirPath = "";
            targets = (""")
for item in targets:
    template.append_content("""
                """ + item.uuid + " /* " + item.name + " */,")
template.append_content("""
            );
        };
/* End PBXProject section */

/* Begin PBXShellScriptBuildPhase section */""")

for item in targets:
    template.append_content(item.PBXShellScriptBuildPhase())

template.append_content("""
/* End PBXShellScriptBuildPhase section */

/* Begin XCBuildConfiguration section */
        """ + uuid_project_buildPhase_debug + """ /* debug */ = {
            isa = XCBuildConfiguration;
            buildSettings = {
                COPY_PHASE_STRIP = NO;
            };
            name = debug;
        };
        """ + uuid_project_buildPhase_release + """ /* release */ = {
            isa = XCBuildConfiguration;
            buildSettings = {
                COPY_PHASE_STRIP = YES;
            };
            name = release;
        };""")

for item in targets:
    template.append_content(item.XCBuildConfiguration())
template.append_content("""
/* End XCBuildConfiguration section */

/* Begin XCConfigurationList section */
        """ + uuid_project_buildConfigurationList + """ /* Build configuration list for PBXProject "$template_library$" */ = {
            isa = XCConfigurationList;
            buildConfigurations = (
                """ + uuid_project_buildPhase_debug + """ /* debug */,
                """ + uuid_project_buildPhase_release + """ /* release */,
            );
            defaultConfigurationIsVisible = 0;
            defaultConfigurationName = release;
        };""")

for item in targets:
    template.append_content(item.XCConfigurationList())
template.append_content("""
/* End XCConfigurationList section */
    };
    rootObject = """ + uuid_project + """ /* Project object */;
}
""")