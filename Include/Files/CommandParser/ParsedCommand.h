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
    struct ParsedCommand
    {
        std::unordered_map<std::string_view, std::string_view> namedArguments;
        std::set<std::string_view> flagArguments;
        std::vector<std::string_view> positionalArguments;
        CommandNodeIndex commandNodeIndex{InvalidCommandNodeIndex};
    };
}
