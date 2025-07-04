//
// Created by Alex on 01/10/2024.
//

#ifndef HX_MATH_VEC3_H
#define HX_MATH_VEC3_H

#include <Hexis/Math/Vector/Operator.h>

namespace Hx
{

	template<u64 S, Arithmetic T, typename Tag>
	struct Vec;

	struct DefaultVecTag;

	template<Arithmetic T, typename Tag>
	using Vec3 = Vec<3, T, Tag>;

	using Vec3f = Vec<3, f32, DefaultVecTag>;
	using Vec3d = Vec<3, f64, DefaultVecTag>;

	template<typename Tag>
	struct Vec<3, f32, Tag>
	{
			Vec(f32 x, f32 y, f32 z);

			f32 x, y, z;
	};

	template<typename Tag>
	struct Vec<3, f64, Tag>
	{
			Vec(f64 x, f64 y, f64 z);

			f64 x, y, z;
	};

	template<Arithmetic T, typename LTag, typename RTag, typename R = typename OperatorRType<3, T, LTag, RTag>::Add>
	typename R::Type operator+(const Vec<3, T, LTag>& lhs, const Vec<3, T, RTag>& rhs);

	template<Arithmetic T, typename Tag, typename R = typename OperatorRType<3, T, Tag, Tag>::Add::Scalar>
	typename R::Type operator+(const Vec<3, T, Tag>& lhs, T scalar);

	template<Arithmetic T, typename LTag, typename RTag, typename R = typename OperatorRType<3, T, LTag, RTag>::Add>
	typename R::Type& operator+=(Vec<3, T, LTag>& lhs, const Vec<3, T, RTag>& rhs);

	template<Arithmetic T, typename Tag, typename R = typename OperatorRType<3, T, Tag, Tag>::Add::Scalar>
	typename R::Type& operator+=(Vec<3, T, Tag>& lhs, T scalar);

	template<Arithmetic T, typename LTag, typename RTag, typename R = typename OperatorRType<3, T, LTag, RTag>::Sub>
	typename R::Type operator-(const Vec<3, T, LTag>& lhs, const Vec<3, T, RTag>& rhs);

	template<Arithmetic T, typename Tag, typename R = typename OperatorRType<3, T, Tag, Tag>::Sub::Scalar>
	typename R::Type operator-(const Vec<3, T, Tag>& lhs, T scalar);

	template<Arithmetic T, typename LTag, typename RTag, typename R = typename OperatorRType<3, T, LTag, RTag>::Sub>
	typename R::Type& operator-=(Vec<3, T, LTag>& lhs, const Vec<3, T, RTag>& rhs);

	template<Arithmetic T, typename Tag, typename R = typename OperatorRType<3, T, Tag, Tag>::Sub::Scalar>
	typename R::Type& operator-=(Vec<3, T, Tag>& lhs, T scalar);

	template<Arithmetic T, typename LTag, typename RTag, typename R = typename OperatorRType<3, T, LTag, RTag>::Mul>
	typename R::Type operator*(const Vec<3, T, LTag>& lhs, const Vec<3, T, RTag>& rhs);

	template<Arithmetic T, typename Tag, typename R = typename OperatorRType<3, T, Tag, Tag>::Mul::Scalar>
	typename R::Type operator*(const Vec<3, T, Tag>& lhs, T scalar);

	template<Arithmetic T, typename LTag, typename RTag, typename R = typename OperatorRType<3, T, LTag, RTag>::Mul>
	typename R::Type& operator*=(Vec<3, T, LTag>& lhs, const Vec<3, T, RTag>& rhs);

	template<Arithmetic T, typename Tag, typename R = typename OperatorRType<3, T, Tag, Tag>::Mul::Scalar>
	typename R::Type& operator*=(Vec<3, T, Tag>& lhs, T scalar);

	template<Arithmetic T, typename LTag, typename RTag, typename R = typename OperatorRType<3, T, LTag, RTag>::Div>
	typename R::Type operator/(const Vec<3, T, LTag>& lhs, const Vec<3, T, RTag>& rhs);

	template<Arithmetic T, typename Tag, typename R = typename OperatorRType<3, T, Tag, Tag>::Div::Scalar>
	typename R::Type operator/(const Vec<3, T, Tag>& lhs, T scalar);

	template<Arithmetic T, typename LTag, typename RTag, typename R = typename OperatorRType<3, T, LTag, RTag>::Div>
	typename R::Type& operator/=(Vec<3, T, LTag>& lhs, const Vec<3, T, RTag>& rhs);

	template<Arithmetic T, typename Tag, typename R = typename OperatorRType<3, T, Tag, Tag>::Div::Scalar>
	typename R::Type& operator/=(Vec<3, T, Tag>& lhs, T scalar);

}

#include <Hexis/Math/Vector/Vec3.inl>

#endif