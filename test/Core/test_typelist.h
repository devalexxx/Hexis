//
// Created by Alex on 30/09/2024.
//

#include <Hexis/Core/TypeList.h>

#include <doctest/doctest.h>

struct T1
{
    static constexpr Hx::u64 index = 0;
};
struct T2
{
    static constexpr Hx::u64 index = 1;
};

template<typename TL>
struct Functor
{
    template<typename T>
    void operator()()
    {
        CHECK(TL::template IndexOf<T> == T::index);
    }
};