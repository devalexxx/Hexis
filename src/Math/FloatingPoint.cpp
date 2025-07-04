//
// Created by Alex on 02/10/2024.
//

#include <Hexis/Math/FloatingPoint.h>

#include <cmath>

namespace Hx
{

	bool Equal(f32 lhs, f32 rhs, f32 epsilon)
	{
		return abs(lhs - rhs) < epsilon;
	}

	bool Equal(f32 lhs, f32 rhs)
	{
		return Equal(lhs, rhs, std::numeric_limits<f32>::epsilon());
	}

	bool Equal(f64 lhs, f64 rhs, f64 epsilon)
	{
		return abs(lhs - rhs) < epsilon;
	}

	bool Equal(f64 lhs, f64 rhs)
	{
		return Equal(lhs, rhs, std::numeric_limits<f64>::epsilon());
	}

}