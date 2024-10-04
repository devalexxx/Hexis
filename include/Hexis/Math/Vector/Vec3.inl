
#include <Hexis/Core/TypeName.h>
#include <Hexis/Math/FloatingPoint.h>

namespace Hx
{

	template<typename Tag>
	Vec<3, f32, Tag>::Vec(f32 x, f32 y, f32 z) :
		x(x), y(y), z(z)
	{}

	template<typename Tag>
	Vec<3, f64, Tag>::Vec(f64 x, f64 y, f64 z) :
		x(x), y(y), z(z)
	{}

	template<Arithmetic T, typename LTag, typename RTag, typename R>
	R::Type operator+(const Vec<3, T, LTag>& lhs, const Vec<3, T, RTag>& rhs)
	{
		return { lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z };
	}

	template<Arithmetic T, typename Tag, typename R>
	R::Type operator+(const Vec<3, T, Tag>& lhs, T scalar)
	{
		return { lhs.x + scalar, lhs.y + scalar, lhs.z + scalar };
	}

	template<Arithmetic T, typename LTag, typename RTag, typename R>
	R::Type& operator+=(Vec<3, T, LTag>& lhs, const Vec<3, T, RTag>& rhs)
	{
		lhs.x += rhs.x;
		lhs.y += rhs.y;
		lhs.z += rhs.z;
		return lhs;
	}

	template<Arithmetic T, typename Tag, typename R>
	R::Type& operator+=(Vec<3, T, Tag>& lhs, T scalar)
	{
		lhs.x += scalar;
		lhs.y += scalar;
		lhs.z += scalar;
		return lhs;
	}

	template<Arithmetic T, typename LTag, typename RTag, typename R>
	R::Type operator-(const Vec<3, T, LTag>& lhs, const Vec<3, T, RTag>& rhs)
	{
		return { lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z };
	}

	template<Arithmetic T, typename Tag, typename R>
	R::Type operator-(const Vec<3, T, Tag>& lhs, T scalar)
	{
		return { lhs.x - scalar, lhs.y - scalar, lhs.z - scalar };
	}

	template<Arithmetic T, typename LTag, typename RTag, typename R>
	R::Type& operator-=(Vec<3, T, LTag>& lhs, const Vec<3, T, RTag>& rhs)
	{
		lhs.x -= rhs.x;
		lhs.y -= rhs.y;
		lhs.z -= rhs.z;
		return lhs;
	}

	template<Arithmetic T, typename Tag, typename R>
	R::Type& operator-=(Vec<3, T, Tag>& lhs, T scalar)
	{
		lhs.x -= scalar;
		lhs.y -= scalar;
		lhs.z -= scalar;
		return lhs;
	}

	template<Arithmetic T, typename LTag, typename RTag, typename R>
	R::Type operator*(const Vec<3, T, LTag>& lhs, const Vec<3, T, RTag>& rhs)
	{
		return { lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z };
	}

	template<Arithmetic T, typename Tag, typename R>
	R::Type operator*(const Vec<3, T, Tag>& lhs, T scalar)
	{
		return { lhs.x * scalar, lhs.y * scalar, lhs.z * scalar };
	}

	template<Arithmetic T, typename LTag, typename RTag, typename R>
	R::Type& operator*=(Vec<3, T, LTag>& lhs, const Vec<3, T, RTag>& rhs)
	{
		lhs.x *= rhs.x;
		lhs.y *= rhs.y;
		lhs.z *= rhs.z;
		return lhs;
	}

	template<Arithmetic T, typename Tag, typename R>
	R::Type& operator*=(Vec<3, T, Tag>& lhs, T scalar)
	{
		lhs.x *= scalar;
		lhs.y *= scalar;
		lhs.z *= scalar;
		return lhs;
	}

	template<Arithmetic T, typename LTag, typename RTag, typename R>
	R::Type operator/(const Vec<3, T, LTag>& lhs, const Vec<3, T, RTag>& rhs)
	{
		return { lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z };
	}

	template<Arithmetic T, typename Tag, typename R>
	R::Type operator/(const Vec<3, T, Tag>& lhs, T scalar)
	{
		return { lhs.x / scalar, lhs.y / scalar, lhs.z / scalar };
	}

	template<Arithmetic T, typename LTag, typename RTag, typename R>
	R::Type& operator/=(Vec<3, T, LTag>& lhs, const Vec<3, T, RTag>& rhs)
	{
		lhs.x /= rhs.x;
		lhs.y /= rhs.y;
		lhs.z /= rhs.z;
		return lhs;
	}

	template<Arithmetic T, typename Tag, typename R>
	R::Type& operator/=(Vec<3, T, Tag>& lhs, T scalar)
	{
		lhs.x /= scalar;
		lhs.y /= scalar;
		lhs.z /= scalar;
		return lhs;
	}

}