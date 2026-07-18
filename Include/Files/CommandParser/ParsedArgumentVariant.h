// Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

#pragma once

#include <CommandParser_Export.h>
#include <CommandParser/Utils.h>
#include <unordered_map>
#include <set>
#include <vector>
#include <string_view>
#include <variant>

namespace CommandParser
{
    namespace ParsedArgumentTypes
    {
        struct COMMANDPARSER_EXPORT Named
        {
            std::pair<std::string_view, std::string_view> Value;
        };

        struct COMMANDPARSER_EXPORT Flag
        {
            std::string_view Value;
        };

        struct COMMANDPARSER_EXPORT Positional
        {
            std::string_view Value;
        };
    }

    using ParsedArgumentVariant = std::variant<ParsedArgumentTypes::Named, ParsedArgumentTypes::Flag, ParsedArgumentTypes::Positional>;
}
