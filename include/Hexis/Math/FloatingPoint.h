//
// Created by Alex on 02/10/2024.
//

#ifndef HX_MATH_FLOATING_POINT_H
#define HX_MATH_FLOATING_POINT_H

#include <Hexis/Core/Types.h>

#include <Hexis/Math/Common.h>

namespace Hx
{

	HX_MATH_API bool Equal(f32 lhs, f32 rhs, f32 epsilon);
	HX_MATH_API bool Equal(f32 lhs, f32 rhs);

	HX_MATH_API bool Equal(f64 lhs, f64 rhs, f64 epsilon);
	HX_MATH_API bool Equal(f64 lhs, f64 rhs);

}

#endif