// Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

#include <CommandParser/ParseFunctions.h>

#include <cassert>
#include <utility>
#include <CppUtils/Core/OverloadedCallable.h>

namespace CommandParser
{
    bool IsCommandNodeChildOf(CommandNodeIndex commandNode, CommandNodeIndex parentNode, std::span<const CommandNodeIndex> commandNodeParentArray)
    {
        CommandNodeIndex actualParentNode = commandNodeParentArray[commandNode];
        return parentNode == actualParentNode;
    }

    ParsedArguments ParseCommandArguments(std::span<const char* const> argumentTokens)
    {
        std::unordered_map<std::string_view, std::string_view> named;
        std::set<std::string_view> flags;
        std::vector<std::string_view> positionals;

        for (const char* token : argumentTokens)
        {
            ParsedArgument commandArgumentVariant = ParseSingleCommandArgument(token);

            std::visit(
                CppUtils::OverloadedCallable{
                    [&named](ParsedArgumentTypes::Named& value)
                    {
                        named.emplace(value.Value.first, value.Value.second);
                    },
                    [&flags](ParsedArgumentTypes::Flag& value)
                    {
                        flags.emplace(value.Value);
                    },
                    [&positionals](ParsedArgumentTypes::Positional& value)
                    {
                        positionals.emplace_back(value.Value);
                    }
                },
                commandArgumentVariant
            );
        }

        return ParsedArguments{
            .Named = std::move(named),
            .Flags = std::move(flags),
            .Positionals = std::move(positionals)
        };
    }

    ParsedArgument ParseSingleCommandArgument(std::string_view token)
    {
        using namespace std::string_view_literals;

        // Handle positional argument case (token is not prefixed with a double dash).
        if (!token.starts_with("--"sv))
        {
            return ParsedArgumentTypes::Positional{token};
        }

        constexpr std::size_t postDoubleDashIndex = 2u;
        const std::string_view tokenPostDoubleDash = token.substr(postDoubleDashIndex);

        // Handle flag argument case (token has no equal character in it).
        const std::size_t equalCharacterIndex = tokenPostDoubleDash.find('=');
        if (equalCharacterIndex == std::string_view::npos) {
            return ParsedArgumentTypes::Flag{tokenPostDoubleDash};
        }

        const std::size_t postEqualCharacterIndex = equalCharacterIndex + 1;

        // Handle named argument case (token contains an equal character).
        return ParsedArgumentTypes::Named{
            std::pair{tokenPostDoubleDash.substr(0u, equalCharacterIndex), tokenPostDoubleDash.substr(postEqualCharacterIndex)}
        };
    }
}
