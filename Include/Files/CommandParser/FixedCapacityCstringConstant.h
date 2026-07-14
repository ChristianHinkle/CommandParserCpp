// Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

#pragma once

#include <CommandParser_Export.h>
#include <cstddef>
#include <string_view>
#include <algorithm>
#include <limits>
#include <CppUtils/Misc/Static_Execute.h>
#include <CppUtils/Core/Bit.h>

namespace CommandParser
{
    /**
     * @brief A struct that stores a cstring in a char buffer, and stores its length as well. This struct is as
     *        lightweight as if it were a raw char buffer (has the same default alignment). Intended to be used in static
     *        storage (e.g., global variables).
     */
    template <std::size_t StructSize>
    struct FixedCapacityCstringConstant
    {
    public:
        static constexpr std::size_t MaxStrlen = StructSize - 2;

        static_assert(MaxStrlen <= std::numeric_limits<unsigned char>::max(), "The max strlen must be small enough for our data member to hold (must fit inside a single unsigned byte).");

        static_assert(StructSize >= 2u, "The specified struct size must be large enough to fit our two data members, which are each the size of a char at least.");

    public:
        template <std::size_t paramCharBufferSize>
            requires (paramCharBufferSize <= MaxStrlen + 1)
        constexpr FixedCapacityCstringConstant(const char (&charBuffer)[paramCharBufferSize])
        {
            // Calculate the cstring's length first.
            Strlen = std::char_traits<char>::length(charBuffer);

            // Copy all the characters up to the null terminator character.
            std::copy_n(charBuffer, Strlen, CharBuffer);
        }

        template <std::size_t otherStructSize>
        constexpr bool operator==(const FixedCapacityCstringConstant<otherStructSize>& other) const
        {
            return Get() == other.Get();
        }

        constexpr bool operator==(const std::string_view otherStringView) const
        {
            return Get() == otherStringView;
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
        constexpr std::string_view Get() const
        {
            // Note: We use our cached strlen value to avoid the string view constructor's strlen calculation (which admittedly is already very fast considering specialized CPU instructions and
            // the fact that these are fairly small string lengths).
            return std::string_view{CharBuffer, Strlen};
        }

    private:
        // Note: [cache] We store the strlen BEFORE the char buffer, so that it is directly beside the data pointer of the cstring. This is beneficial for
        // large struct sizes such as 256 bytes, as that would require multiple cache lines to store. If the strlen data member were stored AFTER the char
        // buffer, then the cstring's data pointer and strlen would be on opposite size of those 256 bytes, which would require the CPU to access two different
        // cache lines whenever you need these data members (e.g., when constructing a string view).

        /**
         * Cached length of the string.
         */
        unsigned char Strlen{};

        /**
         * The backing character buffer to store the cstring.
         */
        char CharBuffer[StructSize - 1]{};
    };

    static_assert(sizeof(FixedCapacityCstringConstant<32>) == 32u, "Test that our desired struct size maches its actual.");

    static_assert(sizeof(FixedCapacityCstringConstant<32>) == sizeof(char[32]), "Test that our struct's size mimics that of an actual raw char buffer.");
    static_assert(alignof(FixedCapacityCstringConstant<32>) == alignof(char[32]), "Test that our struct's alignment mimics that of an actual raw char buffer. If the alignment is any larger than 1u, then that means an unnecessarily large data member or unnecessary padding was introduced in the struct's memory layout somehow. There's no reason the struct can't be as lightweight as a bare char array.");

    static_assert(CppUtils::NumBitsPerByte >= 8u, "Our next static assertion makes this assumption, because we are assuming that single unsigned byte can hold the number 255.");
    CPPUTILS_STATIC_EXECUTE(sizeof(FixedCapacityCstringConstant<256>)); // This type should compile successfully, as 256 minus the 2 extra bytes results in a strlen of 254u, which can fit in 8 bits.
}
