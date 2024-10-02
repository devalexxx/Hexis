
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

	template<Arithmetic To, Arithmetic From, typename Tag>
	requires(ConvertibleTo<From, To>)
	Vec<3, To, Tag> VecTypeCast(const Vec<3, From, Tag>& from)
	{
		return { static_cast<To>(from.x), static_cast<To>(from.y), static_cast<To>(from.z) };
	}

	template<typename ToTag, typename FromTag, Arithmetic T>
	requires(VecAdapter<3, T, FromTag, ToTag>::Cast::value && NotSameAs<FromTag, ToTag>)
	Vec<3, T, ToTag> VecTagCast(const Vec<3, T, FromTag>& from)
	{
		return { from.x, from.y, from.z };
	}

	template<Arithmetic T, typename Tag>
	bool operator==(const Vec<3, T, Tag>& lhs, const Vec<3, T, Tag>& rhs)
	{
		return Equal(lhs.x, rhs.x) && Equal(lhs.y, rhs.y) && Equal(lhs.z, rhs.z);
	}

	template<Arithmetic T, typename Tag>
	bool operator!=(const Vec<3, T, Tag>& lhs, const Vec<3, T, Tag>& rhs)
	{
		return !(lhs == rhs);
	}

	template<Arithmetic T, typename LTag, typename RTag>
	requires(VecAdapter<3, T, LTag, RTag>::Add::value)
	AddVecRType<3, T, LTag, RTag> operator+(const Vec<3, T, LTag>& lhs, const Vec<3, T, RTag>& rhs)
	{
		return { lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z };
	}

	template<Arithmetic T, typename Tag>
	requires(VecAdapter<3, T, Tag, Tag>::SAdd::value)
	Vec<3, T, Tag> operator+(const Vec<3, T, Tag>& lhs, T scalar)
	{
		return { lhs.x + scalar, lhs.y + scalar, lhs.z + scalar };
	}

	template<Arithmetic T, typename LTag, typename RTag>
	requires(VecAdapter<3, T, LTag, RTag>::Add::value)
	Vec<3, T, LTag>& operator+=(Vec<3, T, LTag>& lhs, const Vec<3, T, RTag>& rhs)
	{
		lhs.x += rhs.x;
		lhs.y += rhs.y;
		lhs.z += rhs.z;
		return lhs;
	}

	template<Arithmetic T, typename Tag>
	requires(VecAdapter<3, T, Tag, Tag>::SAdd::value)
	Vec<3, T, Tag>& operator+=(Vec<3, T, Tag>& lhs, T scalar)
	{
		lhs.x += scalar;
		lhs.y += scalar;
		lhs.z += scalar;
		return lhs;
	}

	template<Arithmetic T, typename LTag, typename RTag>
	requires(VecAdapter<3, T, LTag, RTag>::Sub::value)
	SubVecRType<3, T, LTag, RTag> operator-(const Vec<3, T, LTag>& lhs, const Vec<3, T, RTag>& rhs)
	{
		return { lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z };
	}

	template<Arithmetic T, typename Tag>
	requires(VecAdapter<3, T, Tag, Tag>::SSub::value)
	Vec<3, T, Tag> operator-(const Vec<3, T, Tag>& lhs, T scalar)
	{
		return { lhs.x - scalar, lhs.y - scalar, lhs.z - scalar };
	}

	template<Arithmetic T, typename LTag, typename RTag>
	requires(VecAdapter<3, T, LTag, RTag>::Sub::value)
	Vec<3, T, LTag>& operator-=(Vec<3, T, LTag>& lhs, const Vec<3, T, RTag>& rhs)
	{
		lhs.x -= rhs.x;
		lhs.y -= rhs.y;
		lhs.z -= rhs.z;
		return lhs;
	}

	template<Arithmetic T, typename Tag>
	requires(VecAdapter<3, T, Tag, Tag>::SSub::value)
	Vec<3, T, Tag>& operator-=(Vec<3, T, Tag>& lhs, T scalar)
	{
		lhs.x -= scalar;
		lhs.y -= scalar;
		lhs.z -= scalar;
		return lhs;
	}

	template<Arithmetic T, typename LTag, typename RTag>
	requires(VecAdapter<3, T, LTag, RTag>::Mul::value)
	MulVecRType<3, T, LTag, RTag> operator*(const Vec<3, T, LTag>& lhs, const Vec<3, T, RTag>& rhs)
	{
		return { lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z };
	}

	template<Arithmetic T, typename Tag>
	requires(VecAdapter<3, T, Tag, Tag>::SMul::value)
	Vec<3, T, Tag> operator*(const Vec<3, T, Tag>& lhs, T scalar)
	{
		return { lhs.x * scalar, lhs.y * scalar, lhs.z * scalar };
	}

	template<Arithmetic T, typename LTag, typename RTag>
	requires(VecAdapter<3, T, LTag, RTag>::Mul::value)
	Vec<3, T, LTag>& operator*=(Vec<3, T, LTag>& lhs, const Vec<3, T, RTag>& rhs)
	{
		lhs.x *= rhs.x;
		lhs.y *= rhs.y;
		lhs.z *= rhs.z;
		return lhs;
	}

	template<Arithmetic T, typename Tag>
	requires(VecAdapter<3, T, Tag, Tag>::SMul::value)
	Vec<3, T, Tag>& operator*=(Vec<3, T, Tag>& lhs, T scalar)
	{
		lhs.x *= scalar;
		lhs.y *= scalar;
		lhs.z *= scalar;
		return lhs;
	}

	template<Arithmetic T, typename LTag, typename RTag>
	requires(VecAdapter<3, T, LTag, RTag>::Div::value)
	DivVecRType<3, T, LTag, RTag> operator/(const Vec<3, T, LTag>& lhs, const Vec<3, T, RTag>& rhs)
	{
		return { lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z };
	}

	template<Arithmetic T, typename Tag>
	requires(VecAdapter<3, T, Tag, Tag>::SDiv::value)
	Vec<3, T, Tag> operator/(const Vec<3, T, Tag>& lhs, T scalar)
	{
		return { lhs.x / scalar, lhs.y / scalar, lhs.z / scalar };
	}

	template<Arithmetic T, typename LTag, typename RTag>
	requires(VecAdapter<3, T, LTag, RTag>::Div::value)
	Vec<3, T, LTag>& operator/=(Vec<3, T, LTag>& lhs, const Vec<3, T, RTag>& rhs)
	{
		lhs.x /= rhs.x;
		lhs.y /= rhs.y;
		lhs.z /= rhs.z;
		return lhs;
	}

	template<Arithmetic T, typename Tag>
	requires(VecAdapter<3, T, Tag, Tag>::SDiv::value)
	Vec<3, T, Tag>& operator/=(Vec<3, T, Tag>& lhs, T scalar)
	{
		lhs.x /= scalar;
		lhs.y /= scalar;
		lhs.z /= scalar;
		return lhs;
	}

	template<Arithmetic T, typename Tag>
	std::ostream& operator<<(std::ostream& os, const Vec<3, T, Tag>& vec)
	{
		os << "Vec<3, " << TypeName<T>() << ", " << TypeName<Tag>() << ">(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
		return os;
	}

}