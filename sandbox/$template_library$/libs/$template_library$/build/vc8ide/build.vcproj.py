# template file

# Copyright 2007 Stjepan Rajko.
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at
# http://www.boost.org/LICENSE_1_0.txt)

template.append_content(
r"""<?xml version="1.0" encoding="Windows-1252"?>
<VisualStudioProject
	ProjectType="Visual C++"
	Version="8.00"
	Name="build"
	ProjectGUID="{$template_msvc_build_uuid$}"
	>
	<Platforms>
		<Platform
			Name="Win32"
		/>
	</Platforms>
	<ToolFiles>
	</ToolFiles>
	<Configurations>
		<Configuration
			Name="debug|Win32"
			OutputDirectory="..\..\..\..\bin.v2\libs\$(SolutionName)\$(ProjectName)\msvc-8.0\$(ConfigurationName)\threading-multi"
			IntermediateDirectory="$(OutDir)"
			ConfigurationType="0"
			>
			<Tool
				Name="VCNMakeTool"
$template_msvc_build_command$
				Output=""
				PreprocessorDefinitions=""
				IncludeSearchPath=""
				ForcedIncludes=""
				AssemblySearchPath=""
				ForcedUsingAssemblies=""
				CompileAsManaged=""
			/>
		</Configuration>
		<Configuration
			Name="release|Win32"
			OutputDirectory="..\..\..\..\bin.v2\libs\$(SolutionName)\$(ProjectName)\msvc-8.0\$(ConfigurationName)\threading-multi"
			IntermediateDirectory="$(OutDir)"
			ConfigurationType="0"
			>
			<Tool
				Name="VCNMakeTool"
$template_msvc_build_command$
				Output=""
				PreprocessorDefinitions=""
				IncludeSearchPath=""
				ForcedIncludes=""
				AssemblySearchPath=""
				ForcedUsingAssemblies=""
				CompileAsManaged=""
			/>
		</Configuration>
	</Configurations>
	<References>
	</References>
	<Files>""")
vc_list_files(2, r'..\..\..\..', template.replace_name('$template_library$'), 'boost')
template.append_content(r"""
		<Filter
			Name="solution build"
			>
			<File
				RelativePath="..\..\..\..\boost-build.jam"
				>
			</File>
			<File
				RelativePath="..\..\..\..\project-root.jam"
				>
			</File>
			<File
				RelativePath="..\..\..\..\Jamfile.v2"
				>
			</File>
		</Filter>
		<File
			RelativePath="..\..\build\Jamfile.v2"
			>
		</File>
	</Files>
	<Globals>
	</Globals>
</VisualStudioProject>
""")
