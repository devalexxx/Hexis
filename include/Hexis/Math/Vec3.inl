
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

}