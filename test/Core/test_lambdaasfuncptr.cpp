//
// Created by Alex Clorennec on 06/07/2025.
//

#include <doctest/doctest.h>

#include "Hexis/Core/TypeName.h"
#include "Hexis/Core/LambdaAsFuncPtr.h"

#include <functional>

TEST_SUITE("Core")
{
	TEST_CASE("LambdaAsFuncPtr")
	{
		using namespace Hx;

        using ftype_ptr = void(*)(int);

        CHECK(std::is_same_v<decltype(LambdaAsFuncPtr<ftype_ptr>([](int) {})), ftype_ptr>);
    }
}