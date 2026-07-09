// Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

#pragma once

#include <CommandParser/ParseFunctions.h>

#include <cassert>

namespace CommandParser
{
    // TODO: [todo] Implement these stubs.

    template <std::size_t maxCommandNodeNameCharLength>
    std::string GetFullNameOfCommandNode(CommandNodeIndex commandNode, std::span<const char[maxCommandNodeNameCharLength]> commandNodeNameArray, std::span<const CommandNodeIndex> commandNodeParentArray)
    {
        return {};
    }

    template <std::size_t maxCommandNodeNameCharLength>
    void AppendFullNameOfCommandNode(std::string& string, CommandNodeIndex commandNode, std::span<const char[maxCommandNodeNameCharLength]> commandNodeNameArray, std::span<const CommandNodeIndex> commandNodeParentArray)
    {
    }

    template <std::size_t maxCommandNodeNameCharLength>
    ParsedCommandNodeIndex ParseCommandNodeIndex(std::span<const char* const> tokens, std::span<const char[maxCommandNodeNameCharLength]> commandNodeNameArray, std::span<const CommandNodeIndex> commandNodeParentArray)
    {
        return {};
    }

    template <std::size_t maxCommandNodeNameCharLength>
    ParsedCommand ParseCommand(std::span<const char* const> tokens, std::span<const char[maxCommandNodeNameCharLength]> commandNodeNameArray, std::span<const CommandNodeIndex> commandNodeParentArray)
    {
        return {};
    }
}
