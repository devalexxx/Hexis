
#include <Hexis/Core/TypeName.h>

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
	std::ostream& operator<<(std::ostream& os, const Vec<3, T, Tag>& vec)
	{
		os << "Vec<3, " << TypeName<T>() << ", " << TypeName<Tag>() << ">(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
		return os;
	}

}