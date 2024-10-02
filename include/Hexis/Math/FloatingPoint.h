//
// Created by Alex on 02/10/2024.
//

#ifndef HEXIS_MATH_FLOATINGPOINT_H
#define HEXIS_MATH_FLOATINGPOINT_H

#include <Hexis/Math/Common.h>

#include <Hexis/Core/Types.h>

namespace Hx
{

	HEXIS_MATH_API bool Equal(f32 lhs, f32 rhs, f32 epsilon);
	HEXIS_MATH_API bool Equal(f32 lhs, f32 rhs);

	HEXIS_MATH_API bool Equal(f64 lhs, f64 rhs, f64 epsilon);
	HEXIS_MATH_API bool Equal(f64 lhs, f64 rhs);

}

#endif