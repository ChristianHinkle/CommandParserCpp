// Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

#ifndef COMMANDPARSER_INCLUDE_EXPORT_H
#define COMMANDPARSER_INCLUDE_EXPORT_H

// Since interface libraries cannot generate header files during their cmake configuration, we author our
// own "export header" file here, which defines the export macros as a noop.

#define COMMANDPARSER_EXPORT
#define COMMANDPARSER_NO_EXPORT

#endif // #ifndef COMMANDPARSER_INCLUDE_EXPORT_H
