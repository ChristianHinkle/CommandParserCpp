// Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

#ifndef COMMANDPARSER_EXPORT_H
#define COMMANDPARSER_EXPORT_H

// Include the appropriate "export header" file depending on which type of this library is being compiled.

#if __has_include(<commandparser_shared_export.h>)
#   include <commandparser_shared_export.h>
#elif __has_include(<commandparser_module_export.h>)
#   include <commandparser_module_export.h>
#elif __has_include(<commandparser_object_export.h>)
#   include <commandparser_object_export.h>
#elif __has_include(<commandparser_static_export.h>)
#   include <commandparser_static_export.h>
#else
    // Since no generated header files exist, it must mean we are an interface library (being used as a header-only library).
#   include <commandparser_include_export.h>
#endif

// Undef the generated macros that we've decided not to use.

#ifdef COMMANDPARSER_DEPRECATED
#   undef COMMANDPARSER_DEPRECATED
#endif

#ifdef COMMANDPARSER_DEPRECATED_EXPORT
#   undef COMMANDPARSER_DEPRECATED_EXPORT
#endif

#ifdef COMMANDPARSER_DEPRECATED_NO_EXPORT
#   undef COMMANDPARSER_DEPRECATED_NO_EXPORT
#endif

#ifdef COMMANDPARSER_NO_DEPRECATED
#   undef COMMANDPARSER_NO_DEPRECATED
#endif

#endif // #ifndef COMMANDPARSER_EXPORT_H
