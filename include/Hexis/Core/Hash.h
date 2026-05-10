// Copyright (c) 2025 devalexxx
// Distributed under the MIT License.
// https://opensource.org/licenses/MIT

#ifndef HEXIS_CORE_HASH_H
#define HEXIS_CORE_HASH_H

#include <string_view>

namespace Hx
{

    struct STDHash {};

    template<typename, typename = STDHash>
    struct Hash {};

    template<typename T>
    struct Hash<T>
    {
        constexpr u64 operator()(const T& value) const noexcept;
    };

    struct FNV1a64
    {
        static constexpr u64 sOffset = 0xcbf29ce484222325;
        static constexpr u64 sPrime  = 0x00000100000001b3;

        constexpr u64 operator()(const char* value, u64 len) const noexcept;
        constexpr u64 operator()(std::string_view value)        const noexcept;
    };

    template<typename T>
    struct Hash<T, FNV1a64>
    {
        constexpr u64 operator()(const T& value) const noexcept;
    };

    template<typename>
    struct Type {};

    template<typename T>
    struct Hash<Type<T>, FNV1a64>
    {
        constexpr u64 operator()() const noexcept;
    };

}

#include "Hexis/Core/Hash.inl"

#endif
