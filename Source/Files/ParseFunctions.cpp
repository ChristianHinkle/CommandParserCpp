// Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

#include <CommandParser/ParseFunctions.h>

#include <cassert>

namespace CommandParser
{
    // TODO: [todo] Implement these stubs.

    bool IsCommandNodeChildOf(CommandNodeIndex commandNode, CommandNodeIndex parentNode, std::span<const CommandNodeIndex> commandNodeParentArray)
    {
        return {};
    }

    ParsedArgument ParseSingleCommandArgument(std::string_view token)
    {
        return {};
    }

    ParsedArguments ParseCommandArguments(std::span<const std::string_view> argumentTokens)
    {
        return {};
    }
}
