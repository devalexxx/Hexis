//
// Created by Alex on 04/10/2024.
//

#ifndef HX_MATH_TYPE_CAST_H
#define HX_MATH_TYPE_CAST_H

#include <Hexis/Core/Types.h>

namespace Hx
{

	template<u64 S, Arithmetic T, typename Tag>
	struct Vec;

	template<Arithmetic To, Arithmetic From, typename Tag>
	requires ConvertibleTo<From, To>
	inline Vec<3, To, Tag> VecTypeCast(const Vec<3, From, Tag>& from)
	{
		return { static_cast<To>(from.x), static_cast<To>(from.y), static_cast<To>(from.z) };
	}

}

#endif