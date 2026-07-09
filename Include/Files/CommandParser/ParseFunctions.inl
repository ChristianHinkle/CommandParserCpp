// Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

#pragma once

#include <CommandParser/ParseFunctions.h>

#include <cassert>
#include <CppUtils/Core/Algorithm.h>
#include <utility>

namespace CommandParser
{
    template <std::size_t maxCommandNodeNameCharLength>
    std::string GetFullNameOfCommandNode(CommandNodeIndex commandNode, std::span<const char[maxCommandNodeNameCharLength]> commandNodeNameArray, std::span<const CommandNodeIndex> commandNodeParentArray)
    {
        std::string result;
        AppendFullNameOfCommandNode(result,
            commandNode,
            commandNodeNameArray,
            commandNodeParentArray);

        return result;
    }

    template <std::size_t maxCommandNodeNameCharLength>
    void AppendFullNameOfCommandNode(std::string& string, CommandNodeIndex commandNode, std::span<const char[maxCommandNodeNameCharLength]> commandNodeNameArray, std::span<const CommandNodeIndex> commandNodeParentArray)
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
        string.append(std::string_view{commandNodeNameArray[commandNode]});
    }

    template <std::size_t maxCommandNodeNameCharLength>
    ParsedCommandNodeIndex ParseCommandNodeIndex(std::span<const char* const> tokens, std::span<const char[maxCommandNodeNameCharLength]> commandNodeNameArray, std::span<const CommandNodeIndex> commandNodeParentArray)
    {
        CommandNodeIndex commandNodeIndex = InvalidCommandNodeIndex;
        std::size_t numTokensParsed = 0u;

        for (const char* token : tokens)
        {
            // TODO: [todo] Handle duplicate child command node names that have different parents.
            // Note: The `find_if` instead of `find` is necessary here so that we can ignore the extra chars after the null terminating character in the cstring.
            CommandNodeIndex currentTokenCommandNodeIndex = CppUtils::index_find_if(commandNodeNameArray,
                [token](const char commandNodeName[maxCommandNodeNameCharLength])
                {
                    return std::string_view{commandNodeName} == token;
                }
            );

            if (currentTokenCommandNodeIndex == InvalidCommandNodeIndex)
            {
                // This token is not a command node.
                break;
            }

            CommandNodeIndex previousTokenCommandNodeIndex = commandNodeIndex;
            if (previousTokenCommandNodeIndex != InvalidCommandNodeIndex)
            {
                if (!IsCommandNodeChildOf(currentTokenCommandNodeIndex, previousTokenCommandNodeIndex, commandNodeParentArray))
                {
                    // This token is not a child command node of the previous token.
                    break;
                }
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

    template <std::size_t maxCommandNodeNameCharLength>
    ParsedCommand ParseCommandIgnoringTheProgramNameTokenIndex(std::span<const char* const> tokens, std::span<const char[maxCommandNodeNameCharLength]> commandNodeNameArray, std::span<const CommandNodeIndex> commandNodeParentArray)
    {
        return ParseCommand(tokens.subspan(1u), commandNodeNameArray, commandNodeParentArray);
    }

    template <std::size_t maxCommandNodeNameCharLength>
    ParsedCommand ParseCommand(std::span<const char* const> tokens, std::span<const char[maxCommandNodeNameCharLength]> commandNodeNameArray, std::span<const CommandNodeIndex> commandNodeParentArray)
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
