# Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

cmake_minimum_required(VERSION 4.0)

include(${CMAKE_CURRENT_SOURCE_DIR}/CMakeProjectFramework/CMakeProjectFramework.cmake)

set(my_project_name_as_list_split_up_by_namespace "CommandParser")

cmakeprojectframework_mainproject_library_define_project(
  PROJECT_NAME_AS_LIST_SPLIT_UP_BY_NAMESPACE ${my_project_name_as_list_split_up_by_namespace}
  )

cmakeprojectframework_mainproject_library_ctest()

cmakeprojectframework_mainproject_library_add_subprojects(
  PROJECT_NAME_AS_LIST_SPLIT_UP_BY_NAMESPACE ${my_project_name_as_list_split_up_by_namespace}
  )

cmakeprojectframework_mainproject_library_install(
  PROJECT_NAME_AS_LIST_SPLIT_UP_BY_NAMESPACE ${my_project_name_as_list_split_up_by_namespace}
  )

cmakeprojectframework_mainproject_library_cpack()
