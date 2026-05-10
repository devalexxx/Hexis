// Copyright (c) 2025 devalexxx
// Distributed under the MIT License.
// https://opensource.org/licenses/MIT

#include "TypeName.h"
namespace Hx
{

    template<typename T>
    constexpr u64 Hash<T>::operator()(const T& value) const noexcept
    {
        return std::hash<T>{}(value);
    }

    constexpr u64 FNV1a64::operator()(const char* value, const u64 len) const noexcept
    {
        return (*this)(std::string_view{value, len});
    }

    constexpr u64 FNV1a64::operator()(const std::string_view value) const noexcept
    {
        u64 hash = sOffset;
        for (u64 i = 0; i < value.size(); ++i)
        {
            hash ^= value[i];
            hash *= sPrime;
        }
        return hash;
    }

    template<typename T>
    constexpr u64 Hash<T, FNV1a64>::operator()(const T& value) const noexcept
    {
        return FNV1a64{}(value);
    }

    template<typename T>
    constexpr u64 Hash<Type<T>, FNV1a64>::operator()() const noexcept
    {
        return FNV1a64{}(TypeName<T>());
    }

}
