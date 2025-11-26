//
// Created by Alex on 02/10/2024.
//

#include <Hexis/Math/FloatingPoint.h>

#include <doctest/doctest.h>
#include <random>

TEST_SUITE("Core")
{
    TEST_CASE("Equal")
    {
        using namespace Hx;

        SUBCASE("f32")
        {
            std::default_random_engine          gen;
            std::uniform_real_distribution<f32> dist(0.f, 1.f);

            f32 a = dist(gen);
            f32 b = a;
            f32 c = a / b;

            CHECK(Equal(a, b));
            CHECK(Equal(a, c * b));
        }

        SUBCASE("f64")
        {
            std::default_random_engine          gen;
            std::uniform_real_distribution<f64> dist(0.f, 1.f);

            f64 a = dist(gen);
            f64 b = a;
            f64 c = a / b;

            CHECK(Equal(a, b));
            CHECK(Equal(a, c * b));
        }
    }
}