//
// Created by Alex on 30/09/2024.
//

#include "test_typelist.h"

#include <Hexis/Core/Types.h>

TEST_SUITE("Core")
{
    TEST_CASE("Typelist")
    {
        using namespace Hx;

        SUBCASE("Count")
        {
            using TL1 = TypeList<>;
            CHECK_EQ(TL1::Count, 0);

            using TL2 = TypeList<u8, i8>;
            CHECK_EQ(TL2::Count, 2);
        }

        SUBCASE("IndexOf")
        {
            using TL1 = TypeList<u8, i8>;
            CHECK_EQ(TL1::IndexOf<u8>, 0);
            CHECK_EQ(TL1::IndexOf<i8>, 1);
        }

        SUBCASE("TypeAt")
        {
            using TL1 = TypeList<u8, i8>;
            CHECK(std::is_same_v<TL1::TypeAt<0>, u8>);
            CHECK(std::is_same_v<TL1::TypeAt<1>, i8>);
        }

        SUBCASE("Apply")
        {
            using TL1 = TypeList<T1, T2>;
            TL1::Apply<Functor<TL1>>({});
        }
    }
}