//
// Created by Alex on 30/09/2024.
//

#include <doctest/doctest.h>

#include <Hexis/Core/TypeList.h>
#include <Hexis/Core/Types.h>

TEST_SUITE("Core")
{
	TEST_CASE("Typelist")
	{
		using namespace Hx;

		SUBCASE("Size")
		{
			using TL1 = TypeList<>;
			CHECK_EQ(TL1::Size, 0);

			using TL2 = TypeList<u8, i8>;
			CHECK_EQ(TL2::Size, 2);
		}

		SUBCASE("IndexOf")
		{
			using TL1 = TypeList<u8, i8>;
			CHECK_EQ(TL1::IndexOf<u8>, 0);
			CHECK_EQ(TL1::IndexOf<i8>, 1);
			CHECK_EQ(Priv::TypeListIndexOf<0, u8, TL1>::value, 0);
			CHECK_EQ(Priv::TypeListIndexOf<0, i8, TL1>::value, 1);
		}

		SUBCASE("TypeAt")
		{
			using TL1 = TypeList<u8, i8>;
			CHECK(std::is_same_v<TL1::TypeAt<0>, u8>);
			CHECK(std::is_same_v<TL1::TypeAt<1>, i8>);
			CHECK(std::is_same_v<Priv::TypeListTypeAt<0, TL1>::type, u8>);
			CHECK(std::is_same_v<Priv::TypeListTypeAt<1, TL1>::type, i8>);
		}
	}
}