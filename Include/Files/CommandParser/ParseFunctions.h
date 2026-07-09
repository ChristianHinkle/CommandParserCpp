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
    template <std::size_t maxCommandNodeNameCharLength>
    std::string GetFullNameOfCommandNode(CommandNodeIndex commandNode, std::span<const char[maxCommandNodeNameCharLength]> commandNodeNameArray, std::span<const CommandNodeIndex> commandNodeParentArray);
    template <std::size_t maxCommandNodeNameCharLength>
    void AppendFullNameOfCommandNode(std::string& string, CommandNodeIndex commandNode, std::span<const char[maxCommandNodeNameCharLength]> commandNodeNameArray, std::span<const CommandNodeIndex> commandNodeParentArray);

    COMMANDPARSER_EXPORT bool IsCommandNodeChildOf(CommandNodeIndex commandNode, CommandNodeIndex parentNode, std::span<const CommandNodeIndex> commandNodeParentArray);

    struct COMMANDPARSER_EXPORT ParsedCommandNodeIndex
    {
        std::size_t result{InvalidCommandNodeIndex};
        std::size_t numTokensParsed{0u};
    };

    template <std::size_t maxCommandNodeNameCharLength>
    ParsedCommandNodeIndex ParseCommandNodeIndex(std::span<const char* const> tokens, std::span<const char[maxCommandNodeNameCharLength]> commandNodeNameArray, std::span<const CommandNodeIndex> commandNodeParentArray);

    COMMANDPARSER_EXPORT ParsedArgument ParseSingleCommandArgument(std::string_view token);

    struct COMMANDPARSER_EXPORT ParsedArguments
    {
        std::unordered_map<std::string_view, std::string_view> namedArguments;
        std::set<std::string_view> flagArguments;
        std::vector<std::string_view> positionalArguments;
    };

    COMMANDPARSER_EXPORT ParsedArguments ParseCommandArguments(std::span<const std::string_view> argumentTokens);

    template <std::size_t maxCommandNodeNameCharLength>
    ParsedCommand ParseCommand(std::span<const char* const> tokens, std::span<const char[maxCommandNodeNameCharLength]> commandNodeNameArray, std::span<const CommandNodeIndex> commandNodeParentArray);
}

#include <CommandParser/ParseFunctions.inl>
