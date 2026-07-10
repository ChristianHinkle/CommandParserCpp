// Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

#pragma once

#include <CommandParser_Export.h>
#include <cstddef>
#include <string_view>
#include <span>

namespace CommandParser
{
    // TODO: [todo] Delete this. Read TODO comment below about iterators.
    template <std::size_t StringMaxCharLength>
    struct SpanOfMaxLengthCstrings
    {
    public:
        using SpanType = std::span<const char[StringMaxCharLength]>;

    public:
        template <std::size_t ParamArraySize, std::size_t ParamStringMaxCharLength>
        constexpr SpanOfMaxLengthCstrings(const char (&referenceTo2dCharArray)[ParamArraySize][ParamStringMaxCharLength])
            : SpanOf2dCharArray{referenceTo2dCharArray}
        {
        }

        // Note: [cache] Yes this is returning a new pointer (in the form of a string view) to the cstrings rather than using the array directly, but that does not imply a
        // cost of indirection in this case. Because, if we compare these two cases:
        // a) Accessing an element via the array directly: The resulting machine code has the offset to the data baked into the code that's using it.
        // b) Accessing an element via a pointer returned by a function: The pointer is an offset to the data, which is not hardcoded into the machine code, but it is
        //    a pointer stored in a CPU register or even on the stack, which located in a place of hot access and code execution, so we know it's already loaded into
        //    cache at the very least. Also, the compiler will likely inline the implementation of this function, which will result in the offset being baked into the
        //    machine code just like the other case.
        //
        // For an example of where this would be costly: If the pointer to the data was stored somewhere else (not on the stack/registers), then the CPU would first have to load the
        // pointer itself into cache before even being able to use it to access the data.
        constexpr std::string_view operator[](std::size_t index) const
        {
            // TODO: [todo] If we precalculate the length and store it along with these strings, we could directly use that here to construct our string view to
            // avoid the strlen calculation (which admittedly is already very fast considering specialized CPU instructions and the fact that these are fairly small string lengths).
            return SpanOf2dCharArray[index];
        }

    public:

        // TODO: [todo] These iterators when dereferenced would return the raw char arrays instead of a cstring that would successfully compare in an `std::find` algorithm function. We
        // would need to implement a custom iterator with a custom dereference operator that would return the cstring / string view instead of raw char buffer. Another, better solution to this is
        // to avoid having to make this struct entirely, and change the raw 2D array of chars to an array of custom struct which stores the chars and returns a cstring / string view when accessed.

        SpanType::const_iterator begin() const
        {
            return SpanOf2dCharArray.begin();
        }

        SpanType::const_iterator end() const
        {
            return SpanOf2dCharArray.end();
        }

    private:
        SpanType SpanOf2dCharArray;
    };

    template <std::size_t ParamArraySize, std::size_t ParamStringMaxCharLength>
    SpanOfMaxLengthCstrings(const char (&)[ParamArraySize][ParamStringMaxCharLength]) -> SpanOfMaxLengthCstrings<ParamStringMaxCharLength>;
}
