# Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

# @Christian: TODO: [todo][techdebt][cmake] We should probably have the library type determined by the user instead of hard-coding it to static. This goes for our package configuration file as well ("CommandParserConfig.cmake"), in which case, we could probably have it use `find_dependency` for all possible library types used.
find_package(CppUtils_StdReimpl CONFIG REQUIRED COMPONENTS Static)
find_package(CppUtils_Core CONFIG REQUIRED COMPONENTS Static)
find_package(CppUtils_Misc CONFIG REQUIRED COMPONENTS Static)
