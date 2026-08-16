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

        SUBCASE("Member method")
        {
            struct Listener
            {
                i32 callCount     = 0;
                i32 expectedValue = 1;

                void OnEvent(const int& i)
                {
                    callCount++;
                    CHECK_EQ(i, expectedValue++);
                }
            };

            Listener listener;
            auto     handler = bus.Subscribe<int>(&Listener::OnEvent, listener);
            bus.Emit(1);
            CHECK_EQ(listener.callCount, 1);
            bus.Emit(2);
            CHECK_EQ(listener.callCount, 2);
            bus.Withdraw(handler);
            bus.Emit(3);
            CHECK_EQ(listener.callCount, 2);
        }

        SUBCASE("Const member method")
        {
            struct Listener
            {
                mutable i32 callCount     = 0;
                mutable i32 expectedValue = 1;

                void OnEvent(const int& i) const
                {
                    callCount++;
                    CHECK_EQ(i, expectedValue++);
                }
            };

            const Listener listener;
            auto           handler = bus.Subscribe<int>(&Listener::OnEvent, &listener);
            bus.Emit(1);
            CHECK_EQ(listener.callCount, 1);
            bus.Emit(2);
            CHECK_EQ(listener.callCount, 2);
            bus.Withdraw(handler);
            bus.Emit(3);
            CHECK_EQ(listener.callCount, 2);
        }

        SUBCASE("Member method with args")
        {
            struct Listener
            {
                i32 callCount = 0;
                i32 total     = 0;

                void OnEvent(const int& i, i32 multiplier, i32 offset)
                {
                    callCount++;
                    total += i * multiplier + offset;
                }
            };

            Listener listener;
            auto     handler = bus.Subscribe<int>(&Listener::OnEvent, listener, 2, 3);
            bus.Emit(1);
            CHECK_EQ(listener.callCount, 1);
            CHECK_EQ(listener.total, 5);
            bus.Emit(4);
            CHECK_EQ(listener.callCount, 2);
            CHECK_EQ(listener.total, 16);
            bus.Withdraw(handler);
            bus.Emit(8);
            CHECK_EQ(listener.callCount, 2);
            CHECK_EQ(listener.total, 16);
        }
    }
}
