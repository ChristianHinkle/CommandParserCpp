// Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

#pragma once

#include <CommandParser_Export.h>
#include <CommandParser/Utils.h>
#include <unordered_map>
#include <set>
#include <vector>
#include <string_view>

namespace CommandParser
{
    struct COMMANDPARSER_EXPORT ParsedArguments
    {
        std::unordered_map<std::string_view, std::string_view> Named;
        std::set<std::string_view> Flags;
        std::vector<std::string_view> Positionals;
    };
}
