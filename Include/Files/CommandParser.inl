// Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

#pragma once

#include <CommandParser.h>

#include <cassert>
#include <CppUtils/Core/Algorithm.h>
#include <utility>

static_assert(CommandParser::InvalidCommandNodeIndex == static_cast<CommandParser::CommandNodeIndex>(-1), "Several places in our logic rely on this fact.");
static_assert(CommandParser::InvalidCommandNodeIndex == CppUtils::npos, "Several places in our logic rely on this fact.");

namespace CommandParser
{
    template <std::size_t commandNodeNameStructSize>
    std::string GetFullNameOfCommandNode(CommandNodeIndex commandNode, std::span<const FixedCapacityCstringConstant<commandNodeNameStructSize>> commandNodeNameArray, std::span<const CommandNodeIndex> commandNodeParentArray)
    {
        std::string result;
        AppendFullNameOfCommandNode(result,
            commandNode,
            commandNodeNameArray,
            commandNodeParentArray);

        return result;
    }

    template <std::size_t commandNodeNameStructSize>
    void AppendFullNameOfCommandNode(std::string& string, CommandNodeIndex commandNode, std::span<const FixedCapacityCstringConstant<commandNodeNameStructSize>> commandNodeNameArray, std::span<const CommandNodeIndex> commandNodeParentArray)
    {
        if (commandNode == InvalidCommandNodeIndex)
        {
            // The invalid command node's name is represented as an empty string.
            return;
        }

        // Append parent node names first.
        {
            const CommandNodeIndex parentNodeIndex = commandNodeParentArray[commandNode];
            if (parentNodeIndex != InvalidCommandNodeIndex)
            {
                AppendFullNameOfCommandNode(string,
                    parentNodeIndex,
                    commandNodeNameArray,
                    commandNodeParentArray);

                // Separate parent and child node names with a space.
                string.push_back(' ');
            }
        }

        // Append our own node name.
        string.append(commandNodeNameArray[commandNode].Get());
    }

    template <std::size_t commandNodeNameStructSize>
    CommandNodeIndex FindCommandNodeByNameWithParent(std::string_view name, CommandNodeIndex parentNode, std::span<const FixedCapacityCstringConstant<commandNodeNameStructSize>> commandNodeNameArray, std::span<const CommandNodeIndex> commandNodeParentArray)
    {
        CommandNodeIndex currentCommandNodeIndex = InvalidCommandNodeIndex;

        {
            // Search through the name array until we find a match who's parent matches the caller's.
            CommandNodeIndex currentSubspanIndex = CppUtils::index_find(commandNodeNameArray, name);
            while (currentSubspanIndex != InvalidCommandNodeIndex)
            {
                // Note: This logic is a little bit confusing, but it makes sense and it works out. I wouldn't mind this being rewritten in some nicer way.
                // Since the subspan index starts AFTER the previous subspan (subspan's last element plus one), we make sure to offset by one. This also works out
                // for the first iteration, in which the current index is -1, so we happen to conveniently cancel that out with this plus one.
                currentCommandNodeIndex += 1 + currentSubspanIndex;

                if (GetParentCommandNode(currentCommandNodeIndex, commandNodeParentArray) == parentNode)
                {
                    return currentCommandNodeIndex;
                }

                // For the next iteration, search for the name AFTER this last one that we've left off on.
                currentSubspanIndex = CppUtils::index_find(commandNodeNameArray.subspan(currentCommandNodeIndex + 1), name);
            }
        }

        return currentCommandNodeIndex;
    }

    template <std::size_t commandNodeNameStructSize>
    ParsedCommandNodeIndex ParseCommandNodeIndex(std::span<const char* const> tokens, std::span<const FixedCapacityCstringConstant<commandNodeNameStructSize>> commandNodeNameArray, std::span<const CommandNodeIndex> commandNodeParentArray)
    {
        CommandNodeIndex commandNodeIndex = InvalidCommandNodeIndex;
        std::size_t numTokensParsed = 0u;

        for (const std::string_view token : tokens)
        {
            const CommandNodeIndex previousTokenCommandNodeIndex = commandNodeIndex;
            const CommandNodeIndex currentTokenCommandNodeIndex =
                FindCommandNodeByNameWithParent(token, previousTokenCommandNodeIndex, commandNodeNameArray, commandNodeParentArray);

            if (currentTokenCommandNodeIndex == InvalidCommandNodeIndex)
            {
                // This combination of tokens are not a command node.
                break;
            }

            ++numTokensParsed;
            commandNodeIndex = currentTokenCommandNodeIndex;
        }

        if (commandNodeIndex == InvalidCommandNodeIndex)
        {
            assert(numTokensParsed == 0u); // If we got an invalid command node result, the number of tokens parsed should logically be zero.
        }

        return ParsedCommandNodeIndex{
            .Result = commandNodeIndex,
            .NumTokensParsed = numTokensParsed
        };
    }

    template <std::size_t commandNodeNameStructSize>
    ParsedCommand ParseCommandIgnoringTheProgramNameTokenIndex(std::span<const char* const> tokens, std::span<const FixedCapacityCstringConstant<commandNodeNameStructSize>> commandNodeNameArray, std::span<const CommandNodeIndex> commandNodeParentArray)
    {
        return ParseCommand(tokens.subspan(1u), commandNodeNameArray, commandNodeParentArray);
    }

    template <std::size_t commandNodeNameStructSize>
    ParsedCommand ParseCommand(std::span<const char* const> tokens, std::span<const FixedCapacityCstringConstant<commandNodeNameStructSize>> commandNodeNameArray, std::span<const CommandNodeIndex> commandNodeParentArray)
    {
        ParsedCommandNodeIndex parsedCommandNodeIndex = ParseCommandNodeIndex(tokens, commandNodeNameArray, commandNodeParentArray);

        std::span argumentTokens = tokens.subspan(parsedCommandNodeIndex.NumTokensParsed);
        ParsedArguments parsedArguments = ParseCommandArguments(argumentTokens);

        return ParsedCommand{
            .NamedArguments = std::move(parsedArguments.Named),
            .FlagArguments = std::move(parsedArguments.Flags),
            .PositionalArguments = std::move(parsedArguments.Positionals),
            .CommandNodeIndex = parsedCommandNodeIndex.Result
        };
    }
}
