import uuid

class Target(object) :
    def __init__(self, name):
        self.name = name
        self.uuid = uuid.uuid4().get_hex()[0:24]
        self.uuid_buildPhase = uuid.uuid4().get_hex()[0:24]
        self.uuid_buildConfigurationList = uuid.uuid4().get_hex()[0:24]
        self.uuid_buildPhase_debug = uuid.uuid4().get_hex()[0:24]
        self.uuid_buildPhase_release = uuid.uuid4().get_hex()[0:24]
    def PBXAggregateTarget(self):
        return """
        """ + self.uuid + " /* " + self.name + """ */ = {
            isa = PBXAggregateTarget;
            buildConfigurationList = """ + self.uuid_buildConfigurationList + """ /* Build configuration list for PBXAggregateTarget \"""" + self.name + """\" */;
            buildPhases = (
                 """ + self.uuid_buildPhase + """ /* ShellScript */,
            );
            dependencies = (
            );
            name = """ + self.name + """;
            productName = """ + self.name + """;
        };"""

    def PBXShellScriptBuildPhase(self):
        return """
        """ + self.uuid_buildPhase + """ /* ShellScript */ = {
            isa = PBXShellScriptBuildPhase;
            buildActionMask = 2147483647;
            files = (
            );
            inputPaths = (
            );
            outputPaths = (
            );
            runOnlyForDeploymentPostprocessing = 0;
            shellPath = /bin/sh;
            shellScript = \"""" + self.shell_script() + """\";
        };"""

    def XCBuildConfiguration(self) :
        return """
        """ + self.uuid_buildPhase_debug + """ /* debug */ = {
            isa = XCBuildConfiguration;
            buildSettings = {
                COPY_PHASE_STRIP = NO;
                GCC_DYNAMIC_NO_PIC = NO;
                GCC_GENERATE_DEBUGGING_SYMBOLS = YES;
                GCC_OPTIMIZATION_LEVEL = 0;
                PRODUCT_NAME = """ + self.name + """;
            };
            name = debug;
        };
        """ + self.uuid_buildPhase_release + """ /* release */ = {
            isa = XCBuildConfiguration;
            buildSettings = {
                COPY_PHASE_STRIP = YES;
                GCC_ENABLE_FIX_AND_CONTINUE = NO;
                GCC_GENERATE_DEBUGGING_SYMBOLS = NO;
                PRODUCT_NAME = """ + self.name + """;
                ZERO_LINK = NO;
            };
            name = release;
        };"""
        
    def XCConfigurationList(self) :
        return """
        """ + self.uuid_buildConfigurationList + """ /* Build configuration list for PBXAggregateTarget \"""" + self.name + """\" */ = {
            isa = XCConfigurationList;
            buildConfigurations = (
                """ + self.uuid_buildPhase_debug + """ /* debug */,
                """ + self.uuid_buildPhase_release + """ /* release */,
            );
            defaultConfigurationIsVisible = 0;
            defaultConfigurationName = release;
        };"""
        
class Build(Target) :
    def __init__(self, target):
        Target.__init__(self, target)
        self.target = target
    def shell_script(self):
        return "bjam --v2 --toolset=darwin $BUILD_STYLE ../../" + self.target;

class Clean(Target) :
    def __init__(self, target):
        Target.__init__(self, '"' + target + ' clean"')
        self.target = target
    def shell_script(self):
        return "bjam --v2 --clean --toolset=darwin $BUILD_STYLE ../../" + self.target;

class Doc(Target) :
    def __init__(self):
        Target.__init__(self, 'doc')
    def shell_script(self):
        return "cd ../../doc\nbjam --v2 --toolset=darwin release";
    
class DocClean(Target) :
    def __init__(self):
        Target.__init__(self, '"doc clean"')
        self.target = 'doc'
    def shell_script(self):
        return "bjam --v2 --clean --toolset=darwin release ../../" + self.target;
