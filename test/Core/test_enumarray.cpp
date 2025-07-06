//
// Created by Alex Clorennec on 06/07/2025.
//

#include <doctest/doctest.h>

#include "Hexis/Core/EnumArray.h"

enum TEnum
{
    A, B, C, D, Count
};

TEST_SUITE("Core")
{
	TEST_CASE("EnumArray")
	{
		using namespace Hx;

		SUBCASE("Iterator")
        {
            EnumArray<TEnum, int> array {
                { TEnum::A, 1 }, 
                { TEnum::B, 2 }, 
                { TEnum::C, 3 }, 
                { TEnum::D, 4 } 
            };

            for (auto&& [k, v]: array)
            {
                CHECK_EQ(std::to_underlying(k) + 1, v);
            }
        }
    }
}