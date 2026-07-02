# Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

# Set this variable for the person including us to use.
set(TARGETLINKLIBRARIES_CMAKE_RESULT
  # Add dependencies to other targets. For imported targets, it's important to only depend on them if we
  # are BUILD_LOCAL_INTERFACE, because we don't want them to get mixed into our export.
  INTERFACE
    $<BUILD_LOCAL_INTERFACE:CppUtils::StdReimpl::Include>
    $<BUILD_LOCAL_INTERFACE:CppUtils::Core::Include>
    $<BUILD_LOCAL_INTERFACE:CppUtils::Misc::Include>
  )
