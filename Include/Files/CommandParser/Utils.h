// Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

#pragma once

#include <CommandParser_Export.h>
#include <CppUtils/Core/Algorithm.h>
#include <string_view>

namespace CommandParser
{
    using CommandNodeIndex = std::size_t;

    constexpr CommandNodeIndex InvalidCommandNodeIndex = CppUtils::npos;
}

#include <CommandParser/Utils.inl>
