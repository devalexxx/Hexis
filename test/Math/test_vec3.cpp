
#include <doctest/doctest.h>

#include <Hexis/Math/Vec3.h>

#include <random>

struct Tag1 {};
struct Tag2 {};

namespace Hx
{
    template<>
    struct VecAdapter<3, f32, Tag1, Tag2> {
        struct Add : std::true_type { using OTag = Tag1; };

        using Sub  = std::false_type;
        using Mul  = std::false_type;
        using div  = std::false_type;
        using Cast = std::true_type;
    };

    template<>
    struct VecAdapter<3, f32, Tag2, Tag1> {
        struct Sub  : std::true_type { using OTag = Tag1; };

        using Add  = std::false_type;
        using Mul  = std::false_type;
        using div  = std::false_type;
        using Cast = std::true_type;
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

        REQUIRE(sizeof (VecAdapter<3, f32, Tag1, Tag2>) == 1);
        REQUIRE(sizeof (VecAdapter<3, f32, Tag2, Tag1>) == 1);

        SUBCASE("Add")
        {
            Vec3f aa = a;
            Vec3f aAddb { a.x + b.x, a.y + b.y, a.z + b.z };
            CHECK_EQ(aa +  b, aAddb);
            CHECK_EQ(aa += b, aAddb);
            CHECK_EQ(aa     , aAddb);
        }

        SUBCASE("Sub")
        {
            Vec3f aa = a;
            Vec3f aSubb { a.x - b.x, a.y - b.y, a.z - b.z };
            CHECK_EQ(aa -  b, aSubb);
            CHECK_EQ(aa -= b, aSubb);
            CHECK_EQ(aa     , aSubb);
        }

        SUBCASE("Mul")
        {
            Vec3f aa = a;
            Vec3f aMulb { a.x * b.x, a.y * b.y, a.z * b.z };
            CHECK_EQ(aa *  b, aMulb);
            CHECK_EQ(aa *= b, aMulb);
            CHECK_EQ(aa     , aMulb);
        }

        SUBCASE("Div")
        {
            Vec3f aa = a;
            Vec3f aDivb { a.x / b.x, a.y / b.y, a.z / b.z };
            CHECK_EQ(aa /  b, aDivb);
            CHECK_EQ(aa /= b, aDivb);
            CHECK_EQ(aa     , aDivb);
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

            // Following must not compile, because of std::false_type for their operator
            // c -= d; 
            // c -  d;
            // c *= d; 
            // c *  d;
            // c /= d; 
            // c /  d;

            CHECK(std::is_same_v<decltype(d - c), decltype(c)>);
            CHECK(std::is_same_v<std::remove_reference_t<decltype(d -= c)>, decltype(d)>);

            // Following must not compile, because of std::false_type for their operator
            // d += c; 
            // d +  c;
            // d *= c; 
            // d *  c;
            // d /= c; 
            // d /  c;
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