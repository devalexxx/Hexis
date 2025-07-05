//
// Created by Alex on 30/09/2024.
//

#include <doctest/doctest.h>

#include <Hexis/Core/TypeList.h>

struct T1 { static constexpr Hx::u64 index = 0; };
struct T2 { static constexpr Hx::u64 index = 1; };   

template<typename TL>
struct Functor
{
	template<typename T>
	void operator()()
	{
		CHECK(TL::template IndexOf<T> == T::index);
	}
};