// Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

#pragma once

#include <CommandParser_Export.h>
#include <CommandParser/Utils.h>
#include <CppUtils/Core/Concepts.h>
#include <string_view>
#include <string>
#include <span>
#include <CommandParser/ParsedArgument.h>
#include <CommandParser/ParsedCommand.h>

namespace CommandParser
{
    // TODO: [todo] Change these hard-coded-to-std-string functions with string stream instead or something.
    std::string GetFullNameOfCommandNode(CommandNodeIndex commandNode, std::span<const std::string_view> commandNodeNameArray, std::span<const CommandNodeIndex> commandNodeParentArray);
    void AppendFullNameOfCommandNode(std::string& string, CommandNodeIndex commandNode, std::span<const std::string_view> commandNodeNameArray, std::span<const CommandNodeIndex> commandNodeParentArray);

    bool IsCommandNodeChildOf(CommandNodeIndex commandNode, CommandNodeIndex parentNode, std::span<const CommandNodeIndex> commandNodeParentArray);

    struct ParsedCommandNodeIndex
    {
        std::size_t result{InvalidCommandNodeIndex};
        std::size_t numTokensParsed{0u};
    };

    ParsedCommandNodeIndex ParseCommandNodeIndex(std::span<const std::string_view> tokens, std::span<const std::string_view> commandNodeNameArray, std::span<const CommandNodeIndex> commandNodeParentArray);

    ParsedArgument ParseSingleCommandArgument(std::string_view token);

    struct ParsedArguments
    {
        std::unordered_map<std::string_view, std::string_view> namedArguments;
        std::set<std::string_view> flagArguments;
        std::vector<std::string_view> positionalArguments;
    };

    ParsedArguments ParseCommandArguments(std::span<const std::string_view> argumentTokens);

    ParsedCommand ParseCommand(std::span<const std::string_view> tokens, std::span<const std::string_view> commandNodeNameArray, std::span<const CommandNodeIndex> commandNodeParentArray);
}
