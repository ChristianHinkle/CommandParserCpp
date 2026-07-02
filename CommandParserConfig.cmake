# Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

# Write out the main project name here, in one place, to make renaming easier. This is mainly used by our
# boilerplate code. There may be other mentions of the project's name mixed in certain places of this file, so
# don't rely on these variables alone for renaming.
set(my_project_name "CommandParser")
set(my_project_name_target_alias_format "::CommandParser")

include(CMakeFindDependencyMacro)

find_dependency(CppUtils_StdReimpl CONFIG COMPONENTS Include)
find_dependency(CppUtils_Core CONFIG COMPONENTS Include)
find_dependency(CppUtils_Misc CONFIG COMPONENTS Include)

find_dependency(CppUtils_StdReimpl CONFIG COMPONENTS Static)
find_dependency(CppUtils_Core CONFIG COMPONENTS Static)
find_dependency(CppUtils_Misc CONFIG COMPONENTS Static)

# Include our export. This imports all of our targets.
include("${CMAKE_CURRENT_LIST_DIR}/${my_project_name}Export.cmake")

#
# Add alias targets whose names match those from the project file.
#
# It's important to make sure the names are the same for consistency. Namely, so that build
# interface users can use `OVERRIDE_FIND_PACKAGE` with `FetchContent_Declare()`.
#

add_library(${my_project_name_target_alias_format}::Include ALIAS ${my_project_name}_Include)
add_library(${my_project_name_target_alias_format}::Source ALIAS ${my_project_name}_Source)
add_library(${my_project_name_target_alias_format}::Static ALIAS ${my_project_name}_Static)
add_library(${my_project_name_target_alias_format}::Shared ALIAS ${my_project_name}_Shared)
add_library(${my_project_name_target_alias_format}::Module ALIAS ${my_project_name}_Module)
add_library(${my_project_name_target_alias_format}::Object ALIAS ${my_project_name}_Object)
