//
// Created by Alex on 01/10/2024.
//

#ifndef HEXIS_MATH_VEC3_H
#define HEXIS_MATH_VEC3_H

#include <Hexis/Math/Vec.h>

#include <ostream>

namespace Hx
{

	template<typename Tag>
	struct Vec<3, f32, Tag>
	{
			Vec(f32 x, f32 y, f32 z);

			f32 x, y, z;
	};
	using Vec3f = Vec<3, f32, DefaultVecTag>;

	template<typename Tag>
	struct Vec<3, f64, Tag>
	{
			Vec(f64 x, f64 y, f64 z);

			f64 x, y, z;
	};
	using Vec3d = Vec<3, f64, DefaultVecTag>;

	template<Arithmetic T, typename Tag>
	using Vec3 = Vec<3, T, Tag>;

	template<Arithmetic T, typename Tag>
	std::ostream& operator<<(std::ostream& os, const Vec<3, T, Tag>& vec);

}

#include <Hexis/Math/Vec3.inl>

#endif