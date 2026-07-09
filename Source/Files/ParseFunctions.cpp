// Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

#include <CommandParser/ParseFunctions.h>

#include <cassert>

namespace CommandParser
{
    bool IsCommandNodeChildOf(CommandNodeIndex commandNode, CommandNodeIndex parentNode, std::span<const CommandNodeIndex> commandNodeParentArray)
    {
        CommandNodeIndex actualParentNode = commandNodeParentArray[commandNode];
        return parentNode == actualParentNode;
    }

    ParsedArgument ParseSingleCommandArgument(std::string_view token)
    {
        // TODO: [todo] Implement this stub.
        return {};
    }

    ParsedArguments ParseCommandArguments(std::span<const char* const> argumentTokens)
    {
        // TODO: [todo] Implement this stub.
        return {};
    }
}
