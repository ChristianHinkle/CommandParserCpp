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
    // TODO: [todo] Implement this variant of different argument types.

    namespace ParsedArgumentTypes
    {
        struct Named
        {
        };

        struct Flag
        {
        };

        struct Positional
        {
        };
    }

    using ParsedArgument = std::variant<ParsedArgumentTypes::Named, ParsedArgumentTypes::Flag, ParsedArgumentTypes::Positional>;
}
