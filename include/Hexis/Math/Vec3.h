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

	template<Arithmetic To, Arithmetic From, typename Tag>
	requires(ConvertibleTo<From, To>)
	Vec<3, To, Tag> VecTypeCast(const Vec<3, From, Tag>& from);

	template<typename ToTag, typename FromTag, Arithmetic T>
	requires(VecAdapter<3, T, FromTag, ToTag>::Cast::value && NotSameAs<FromTag, ToTag>)
	Vec<3, T, ToTag> VecTagCast(const Vec<3, T, FromTag>& from);

	template<Arithmetic T, typename Tag>
	bool operator==(const Vec<3, T, Tag>& lhs, const Vec<3, T, Tag>& rhs);

	template<Arithmetic T, typename Tag>
	bool operator!=(const Vec<3, T, Tag>& lhs, const Vec<3, T, Tag>& rhs);

	template<Arithmetic T, typename LTag, typename RTag>
	requires(VecAdapter<3, T, LTag, RTag>::Add::value)
	AddVecRType<3, T, LTag, RTag> operator+(const Vec<3, T, LTag>& lhs, const Vec<3, T, RTag>& rhs);

	template<Arithmetic T, typename Tag>
	requires(VecAdapter<3, T, Tag, Tag>::SAdd::value)
	Vec<3, T, Tag> operator+(const Vec<3, T, Tag>& lhs, T scalar);

	template<Arithmetic T, typename LTag, typename RTag>
	requires(VecAdapter<3, T, LTag, RTag>::Add::value)
	Vec<3, T, LTag>& operator+=(Vec<3, T, LTag>& lhs, const Vec<3, T, RTag>& rhs);

	template<Arithmetic T, typename Tag>
	requires(VecAdapter<3, T, Tag, Tag>::SAdd::value)
	Vec<3, T, Tag>& operator+=(Vec<3, T, Tag>& lhs, T scalar);

	template<Arithmetic T, typename LTag, typename RTag>
	requires(VecAdapter<3, T, LTag, RTag>::Sub::value)
	SubVecRType<3, T, LTag, RTag> operator-(const Vec<3, T, LTag>& lhs, const Vec<3, T, RTag>& rhs);

	template<Arithmetic T, typename Tag>
	requires(VecAdapter<3, T, Tag, Tag>::SSub::value)
	Vec<3, T, Tag> operator-(const Vec<3, T, Tag>& lhs, T scalar);

	template<Arithmetic T, typename LTag, typename RTag>
	requires(VecAdapter<3, T, LTag, RTag>::Sub::value)
	Vec<3, T, LTag>& operator-=(Vec<3, T, LTag>& lhs, const Vec<3, T, RTag>& rhs);

	template<Arithmetic T, typename Tag>
	requires(VecAdapter<3, T, Tag, Tag>::SSub::value)
	Vec<3, T, Tag>& operator-=(Vec<3, T, Tag>& lhs, T scalar);

	template<Arithmetic T, typename LTag, typename RTag>
	requires(VecAdapter<3, T, LTag, RTag>::Mul::value)
	MulVecRType<3, T, LTag, RTag> operator*(const Vec<3, T, LTag>& lhs, const Vec<3, T, RTag>& rhs);

	template<Arithmetic T, typename Tag>
	requires(VecAdapter<3, T, Tag, Tag>::SMul::value)
	Vec<3, T, Tag> operator*(const Vec<3, T, Tag>& lhs, T scalar);

	template<Arithmetic T, typename LTag, typename RTag>
	requires(VecAdapter<3, T, LTag, RTag>::Mul::value)
	Vec<3, T, LTag>& operator*=(Vec<3, T, LTag>& lhs, const Vec<3, T, RTag>& rhs);

	template<Arithmetic T, typename Tag>
	requires(VecAdapter<3, T, Tag, Tag>::SMul::value)
	Vec<3, T, Tag>& operator*=(Vec<3, T, Tag>& lhs, T scalar);

	template<Arithmetic T, typename LTag, typename RTag>
	requires(VecAdapter<3, T, LTag, RTag>::Div::value)
	DivVecRType<3, T, LTag, RTag> operator/(const Vec<3, T, LTag>& lhs, const Vec<3, T, RTag>& rhs);

	template<Arithmetic T, typename Tag>
	requires(VecAdapter<3, T, Tag, Tag>::SDiv::value)
	Vec<3, T, Tag> operator/(const Vec<3, T, Tag>& lhs, T scalar);

	template<Arithmetic T, typename LTag, typename RTag>
	requires(VecAdapter<3, T, LTag, RTag>::Div::value)
	Vec<3, T, LTag>& operator/=(Vec<3, T, LTag>& lhs, const Vec<3, T, RTag>& rhs);

	template<Arithmetic T, typename Tag>
	requires(VecAdapter<3, T, Tag, Tag>::SDiv::value)
	Vec<3, T, Tag>& operator/=(Vec<3, T, Tag>& lhs, T scalar);

	template<Arithmetic T, typename Tag>
	std::ostream& operator<<(std::ostream& os, const Vec<3, T, Tag>& vec);

}

#include <Hexis/Math/Vec3.inl>

#endif