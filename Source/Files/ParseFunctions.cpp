// Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

#include <CommandParser/ParseFunctions.h>

namespace CommandParser
{
    // TODO: [todo] Implement these stubs.

    std::string GetFullNameOfCommandNode(CommandNodeIndex commandNode, std::span<const std::string_view> commandNodeNameArray, std::span<const CommandNodeIndex> commandNodeParentArray)
    {
        return {};
    }

    void AppendFullNameOfCommandNode(std::string& string, CommandNodeIndex commandNode, std::span<const std::string_view> commandNodeNameArray, std::span<const CommandNodeIndex> commandNodeParentArray)
    {
    }

    bool IsCommandNodeChildOf(CommandNodeIndex commandNode, CommandNodeIndex parentNode, std::span<const CommandNodeIndex> commandNodeParentArray)
    {
        return {};
    }

    ParsedCommandNodeIndex ParseCommandNodeIndex(std::span<const std::string_view> tokens, std::span<const std::string_view> commandNodeNameArray, std::span<const CommandNodeIndex> commandNodeParentArray)
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

    ParsedCommand ParseCommand(std::span<const std::string_view> tokens, std::span<const std::string_view> commandNodeNameArray, std::span<const CommandNodeIndex> commandNodeParentArray)
    {
        return {};
    }
}
