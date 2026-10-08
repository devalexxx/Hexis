// Copyright (c) 2025 devalexxx
// Distributed under the MIT License.
// https://opensource.org/licenses/MIT

#include "Hexis/Core/PackedValArray.h"
#include <doctest/doctest.h>

TEST_SUITE("Core")
{
    TEST_CASE("PackedValArray")
    {
        using namespace Hx;

        SUBCASE("Size")
        {
            PackedValArray array(3, 3);
            CHECK_EQ(array.GetContainerSize(), 1);
            CHECK_EQ(array.GetOverflow(), 64 - 9);
            CHECK_EQ(array.GetSize(), 3);
            CHECK_EQ(array.GetValueSize(), 3);
        }

        SUBCASE("Values")
        {
            PackedValArray a(3, 5);
            a.Set(0, 0);
            a.Set(1, 1);
            a.Set(2, 2);
            CHECK_EQ(a.Get(0), 0);
            CHECK_EQ(a.Get(1), 1);
            CHECK_EQ(a.Get(2), 2);
        }

    }
}