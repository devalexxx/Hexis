//
// Created by Alex on 04/10/2024.
//

#ifndef HEXIS_MATH_VECTOR_STRING_H
#define HEXIS_MATH_VECTOR_STRING_H

#include <Hexis/Core/TypeName.h>

#include <Hexis/Math/Vector/Vec3.h>

#include <sstream>
#include <ostream>

namespace Hx
{

	template<Arithmetic T, typename Tag>
	inline std::string ToString(const Vec<3, T, Tag>& v)
	{
		std::stringstream sstr;
		sstr << "Vec<3, " << TypeName<T>() << ", " << TypeName<Tag>() << ">(" << v.x << ", " << v.y << ", " << v.z << ")";
		return sstr.str();
	}

	template<Arithmetic T, typename Tag>
	inline std::ostream& operator<<(std::ostream& os, const Vec<3, T, Tag>& v)
	{
		os << ToString(v);
		return os;
	}

}

#endif