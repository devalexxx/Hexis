//
// Created by Alex on 01/10/2024.
//

#ifndef HX_MATH_VEC_H
#define HX_MATH_VEC_H

#include <Hexis/Core/Types.h>

namespace Hx
{

	struct DefaultVecTag
	{};

	template<u64 S, Arithmetic T, typename Tag>
	struct Vec
	{};

}

#include <Hexis/Math/Vector/Vec3.h>

#include <Hexis/Math/Vector/TagCast.h>
#include <Hexis/Math/Vector/TypeCast.h>

#endif