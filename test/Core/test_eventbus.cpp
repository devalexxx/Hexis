//
// Created by Alex Clorennec on 06/07/2025.
//

#include "Hexis/Core/EventBus.h"
#include <doctest/doctest.h>

TEST_SUITE("Core")
{
    TEST_CASE("EventBus")
    {
        using namespace Hx;
        EventBus bus;

        SUBCASE("Withdraw")
        {
            auto handler = bus.Subscribe<int>([](const int&) {});
            bus.Withdraw(handler);
            bus.Withdraw(handler);
        }

        SUBCASE("Emit")
        {
            i32 callCount = 0, expectedValue = 1;
            auto handler = bus.Subscribe<int>([&](const int& i)
            {
                callCount++;
                CHECK_EQ(i, expectedValue++);
            });
            bus.Emit(1);
            CHECK_EQ(callCount, 1);
            bus.Emit(2);
            CHECK_EQ(callCount, 2);
            bus.Withdraw(handler);
            bus.Emit(3);
            CHECK_EQ(callCount, 2);
        }

        SUBCASE("Enqueue")
        {
            i32 callCount = 0, expectedValue = 1;
            auto handler = bus.Subscribe<int>([&](const int& i)
            {
                callCount++;
                CHECK_EQ(i, expectedValue++);
            });
            bus.Enqueue(1);
            CHECK_EQ(callCount, 0);
            bus.Poll();
            CHECK_EQ(callCount, 1);
            bus.Enqueue(2);
            CHECK_EQ(callCount, 1);
            bus.Enqueue(3);
            CHECK_EQ(callCount, 1);
            bus.Poll();
            CHECK_EQ(callCount, 3);
            bus.Withdraw(handler);
            bus.Enqueue(4);
            CHECK_EQ(callCount, 3);
        }
    }
}
