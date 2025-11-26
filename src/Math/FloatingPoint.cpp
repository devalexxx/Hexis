//
// Created by Alex on 02/10/2024.
//

#include <Hexis/Math/FloatingPoint.h>

#include <cmath>

namespace Hx
{

    bool Equal(const f32 lhs, const f32 rhs, const f32 epsilon)
    {
        return std::abs(lhs - rhs) < epsilon;
    }

    bool Equal(const f32 lhs, const f32 rhs)
    {
        return Equal(lhs, rhs, std::numeric_limits<f32>::epsilon());
    }

    bool Equal(const f64 lhs, const f64 rhs, const f64 epsilon)
    {
        return std::abs(lhs - rhs) < epsilon;
    }

    bool Equal(const f64 lhs, const f64 rhs)
    {
        return Equal(lhs, rhs, std::numeric_limits<f64>::epsilon());
    }

}