//
// Created by Alex on 04/10/2024.
//

#ifndef HX_MATH_EQUALITY_H
#define HX_MATH_EQUALITY_H

#include <Hexis/Math/Vector/Vec3.h>

namespace Hx
{

	template<Arithmetic T, typename Tag>
	requires std::is_floating_point_v<T>
	inline bool Equal(const Vec<3, T, Tag>& lhs, const Vec<3, T, Tag>& rhs, T epsilon)
	{
		return Equal(lhs.x, rhs.x, epsilon) && Equal(lhs.y, rhs.y, epsilon) && Equal(lhs.z, rhs.z, epsilon);
	}

	template<Arithmetic T, typename Tag>
	inline bool Equal(const Vec<3, T, Tag>& lhs, const Vec<3, T, Tag>& rhs)
	{
		return Equal(lhs.x, rhs.x) && Equal(lhs.y, rhs.y) && Equal(lhs.z, rhs.z);
	}

	template<Arithmetic T, typename Tag>
	inline bool operator==(const Vec<3, T, Tag>& lhs, const Vec<3, T, Tag>& rhs)
	{
		return Equal(lhs, rhs);
	}

	template<Arithmetic T, typename Tag>
	inline bool operator!=(const Vec<3, T, Tag>& lhs, const Vec<3, T, Tag>& rhs)
	{
		return !(lhs == rhs);
	}


}

#endif
