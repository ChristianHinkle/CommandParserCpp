// Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

#pragma once

#include <CommandParser_Export.h>
#include <CommandParser/Utils.h>
#include <CppUtils/Core/Concepts.h>
#include <string_view>
#include <string>
#include <span>
#include <CommandParser/ParsedArgumentVariant.h>
#include <CommandParser/ParsedArguments.h>
#include <CommandParser/ParsedCommand.h>
#include <CommandParser/FixedCapacityCstringConstant.h>

namespace CommandParser
{
    // TODO: [todo] Change these hard-coded-to-std-string functions with string stream instead or something.
    template <std::size_t commandNodeNameStructSize>
    std::string GetFullNameOfCommandNode(CommandNodeIndex commandNode, std::span<const FixedCapacityCstringConstant<commandNodeNameStructSize>> commandNodeNameArray, std::span<const CommandNodeIndex> commandNodeParentArray);

    template <std::size_t commandNodeNameStructSize>
    void AppendFullNameOfCommandNode(std::string& string, CommandNodeIndex commandNode, std::span<const FixedCapacityCstringConstant<commandNodeNameStructSize>> commandNodeNameArray, std::span<const CommandNodeIndex> commandNodeParentArray);

    COMMANDPARSER_EXPORT CommandNodeIndex GetParentCommandNode(CommandNodeIndex commandNodeIndex, std::span<const CommandNodeIndex> commandNodeParentArray);

    template <std::size_t commandNodeNameStructSize>
    CommandNodeIndex FindCommandNodeByNameWithParent(std::string_view name, CommandNodeIndex parentNode, std::span<const FixedCapacityCstringConstant<commandNodeNameStructSize>> commandNodeNameArray, std::span<const CommandNodeIndex> commandNodeParentArray);

    struct COMMANDPARSER_EXPORT ParsedCommandNodeIndex
    {
        std::size_t Result{InvalidCommandNodeIndex};
        std::size_t NumTokensParsed{0u};
    };

    template <std::size_t commandNodeNameStructSize>
    ParsedCommandNodeIndex ParseCommandNodeIndex(std::span<const char* const> tokens, std::span<const FixedCapacityCstringConstant<commandNodeNameStructSize>> commandNodeNameArray, std::span<const CommandNodeIndex> commandNodeParentArray);

    COMMANDPARSER_EXPORT ParsedArguments ParseCommandArguments(std::span<const char* const> argumentTokens);

    COMMANDPARSER_EXPORT ParsedArgumentVariant ParseSingleCommandArgument(std::string_view token);

    template <std::size_t commandNodeNameStructSize>
    ParsedCommand ParseCommandIgnoringTheProgramNameTokenIndex(std::span<const char* const> tokens, std::span<const FixedCapacityCstringConstant<commandNodeNameStructSize>> commandNodeNameArray, std::span<const CommandNodeIndex> commandNodeParentArray);

    template <std::size_t commandNodeNameStructSize>
    ParsedCommand ParseCommand(std::span<const char* const> tokens, std::span<const FixedCapacityCstringConstant<commandNodeNameStructSize>> commandNodeNameArray, std::span<const CommandNodeIndex> commandNodeParentArray);
}

#include <CommandParser.inl>
