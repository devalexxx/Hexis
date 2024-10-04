
#include <doctest/doctest.h>

#include <Hexis/Math/Vec.h>
#include <Hexis/Math/Vector/Equality.h>
#include <Hexis/Math/Vector/String.h>
#include <Hexis/Math/Vector/TypeCast.h>
#include <Hexis/Math/Vector/TagCast.h>

#include <random>
#include <iostream>

struct Tag1 {};
struct Tag2 {};

namespace Hx
{

    template<typename Tag>
    struct Vec<3, i32, Tag>
    {
        i32 x, y, z;
    };

    template<typename T>
    struct VecAdapter<3, T, Tag1, Tag2> {
        struct Cast 
        {
            using OTag = Tag2;
        };

        struct Add 
        { 
            using OTag = Tag1; 
            struct Scalar
            {
                using OTag = Tag1;
            };
        };
    };

    template<typename T>
    struct VecAdapter<3, T, Tag2, Tag1> {
        struct Cast 
        {
            using OTag = Tag1;
        };

        struct Sub 
        { 
            using OTag = Tag2; 
        };
    };

}

TEST_SUITE("Math")
{

    TEST_CASE("Vec3")
    {
        using namespace Hx;

        std::default_random_engine          gen;
        std::uniform_real_distribution<f32> dist(0.f, 1.f);
    
        Vec3f a { dist(gen), dist(gen), dist(gen) };
		Vec3f b { dist(gen), dist(gen), dist(gen) };
        f32   s { dist(gen) };

        REQUIRE(sizeof (VecAdapter<3, f32, Tag1, Tag2>) == 1);
        REQUIRE(sizeof (VecAdapter<3, f32, Tag2, Tag1>) == 1);

        SUBCASE("Add")
        {
            Vec3f aa = a;
            Vec3f r { a.x + b.x, a.y + b.y, a.z + b.z };
            CHECK_EQ(aa +  b, r);
            CHECK_EQ(aa += b, r);
            CHECK_EQ(aa     , r);
        }

        SUBCASE("ScalarAdd")
        {
            Vec3f aa = a;
            Vec3f r { a.x + s, a.y + s, a.z + s };
            CHECK_EQ(aa +  s, r);
            CHECK_EQ(aa += s, r);
            CHECK_EQ(aa     , r);
        }

        SUBCASE("Sub")
        {
            Vec3f aa = a;
            Vec3f r { a.x - b.x, a.y - b.y, a.z - b.z };
            CHECK_EQ(aa -  b, r);
            CHECK_EQ(aa -= b, r);
            CHECK_EQ(aa     , r);
        }

        SUBCASE("ScalarSub")
        {
            Vec3f aa = a;
            Vec3f r { a.x - s, a.y - s, a.z - s };
            CHECK_EQ(aa -  s, r);
            CHECK_EQ(aa -= s, r);
            CHECK_EQ(aa     , r);
        }

        SUBCASE("Mul")
        {
            Vec3f aa = a;
            Vec3f r { a.x * b.x, a.y * b.y, a.z * b.z };
            CHECK_EQ(aa *  b, r);
            CHECK_EQ(aa *= b, r);
            CHECK_EQ(aa     , r);
        }

        SUBCASE("ScalarMul")
        {
            Vec3f aa = a;
            Vec3f r { a.x * s, a.y * s, a.z * s };
            CHECK_EQ(aa *  s, r);
            CHECK_EQ(aa *= s, r);
            CHECK_EQ(aa     , r);
        }

        SUBCASE("Div")
        {
            Vec3f aa = a;
            Vec3f r { a.x / b.x, a.y / b.y, a.z / b.z };
            CHECK_EQ(aa /  b, r);
            CHECK_EQ(aa /= b, r);
            CHECK_EQ(aa     , r);
        }

        SUBCASE("ScalarDiv")
        {
            Vec3f aa = a;
            Vec3f r { a.x / s, a.y / s, a.z / s };
            CHECK_EQ(aa /  s, r);
            CHECK_EQ(aa /= s, r);
            CHECK_EQ(aa     , r);
        }

        SUBCASE("TypeCast")
        {
            Vec3f  a = { dist(gen), dist(gen), dist(gen) };
            Vec3d b = VecTypeCast<f64>(a);

            CHECK_EQ(a, VecTypeCast<f32>(b));
        }

        SUBCASE("Tag")
        {
            Vec3<f32, Tag1> c { 1.f, 2.f, 3.f };
            Vec3<f32, Tag2> d { 1.f, 2.f, 3.f };

            CHECK(std::is_same_v<decltype(c + d), decltype(c)>);
            CHECK(std::is_same_v<std::remove_reference_t<decltype(c += d)>, decltype(c)>);
            CHECK(std::is_same_v<decltype(c + s), decltype(c)>);
            CHECK(std::is_same_v<std::remove_reference_t<decltype(c += s)>, decltype(c)>);

            // Following must not compile, because of std::false_type for their operator
            // c -= d; 
            // c -  d;
            // c *= d; 
            // c *  d;
            // c /= d; 
            // c /  d;
            // c -= s; 
            // c -  s;
            // c *= s; 
            // c *  s;
            // c /= s; 
            // c /  s;

            CHECK(std::is_same_v<decltype(d - c), decltype(d)>);
            CHECK(std::is_same_v<std::remove_reference_t<decltype(d -= c)>, decltype(d)>);

            // Following must not compile, because of std::false_type for their operator
            // d += c; 
            // d +  c;
            // d *= c; 
            // d *  c;
            // d /= c; 
            // d /  c;
            // d += s; 
            // d +  s;
            // c -= s; 
            // c -  s;
            // d *= s; 
            // d *  s;
            // d /= s; 
            // d /  s;
        }

        SUBCASE("TagCast")
        {
            Vec3<f32, Tag1> c { 1.f, 2.f, 3.f };
            Vec3<f32, Tag2> d = VecTagCast<Tag2>(c);
            Vec3<f32, Tag1> e { 0.f, 0.f, 0.f };

            // Must not compile
            // c - d;

            CHECK(std::is_same_v<decltype(c), decltype(VecTagCast<Tag1>(d))>);

            e = VecTagCast<Tag1>(d);
            CHECK_EQ(c, e);
        }

    }

}