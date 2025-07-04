//
// Created by Alex on 04/10/2024.
//

#ifndef HX_MATH_TAG_CAST_H
#define HX_MATH_TAG_CAST_H

#include <Hexis/Core/Types.h>

#include <Hexis/Math/Vector/Operator.h>

namespace Hx
{

	template<u64 S, Arithmetic T, typename Tag>
	struct Vec;

	template<u64 S, Arithmetic T, typename LTag, typename RTag>
	struct VecAdapter;

	template<typename TTag, typename FTag, Arithmetic T, typename R = typename OperatorRType<3, T, FTag, TTag>::Cast>
	inline typename R::Type VecTagCast(const Vec<3, T, FTag>& from)
	{
		return { from.x, from.y, from.z };
	}

}

#endif