//
// Created by Alex Clorennec on 19/11/2025.
//

#include "Hexis/Core/TaskScheduler.h"
#include "Hexis/Core/TypeName.h"

#include <doctest/doctest.h>

TEST_SUITE("Core")
{
    TEST_CASE("TaskScheduler")
    {
        Hx::TaskScheduler scheduler;

        SUBCASE("scheduler-freeze")
        {
            scheduler.Freeze();
            scheduler.Insert([]{}).Enqueue();
            CHECK_EQ(scheduler.GetTaskCount(), 1);
            scheduler.Resume();
            scheduler.Join();
            CHECK_EQ(scheduler.GetTaskCount(), 0);
        }

        SUBCASE("scheduler-accept")
        {
            scheduler.Freeze();
            scheduler.Insert([]{}).Enqueue();
            scheduler.Insert([]{}).Enqueue();
            scheduler.Accept();
            while (scheduler.GetTaskCount() > 1 || scheduler.GetActiveWorkerCount() > 0) {}
            CHECK_EQ(scheduler.GetTaskCount(), 1);
            scheduler.Resume();
            scheduler.Join();
            CHECK_EQ(scheduler.GetTaskCount(), 0);
        }

        SUBCASE("task-join")
        {
            for (size_t j = 0; j < scheduler.GetWorkerCount(); j++)
            {
                scheduler.Insert([]() {}).Enqueue();
            }
            scheduler.Join();
            CHECK_EQ(scheduler.GetTaskCount(), 0);
            CHECK_EQ(scheduler.GetActiveWorkerCount(), 0);
        }

        SUBCASE("task-async-join")
        {
            for (size_t j = 0; j < scheduler.GetWorkerCount(); j++)
            {
                scheduler.Insert([]() {}).Enqueue();
            }
            scheduler.StartJoin();
            while (!scheduler.IsJoined()) {}
            scheduler.StopJoin();
            CHECK_EQ(scheduler.GetTaskCount(), 0);
            CHECK_EQ(scheduler.GetActiveWorkerCount(), 0);
        }

        SUBCASE("task-group-join")
        {
            scheduler.Freeze();
            for (size_t j = 0; j < scheduler.GetWorkerCount(); j++)
            {
                scheduler.Insert([]() {})
                    .SetGroup("any_group")
                    .AsUnique()
                    .Enqueue()
                    .Cancel();
            }
            for (size_t j = 0; j < scheduler.GetWorkerCount(); j++)
            {
                scheduler.Insert([]() {}).Enqueue();
            }
            scheduler.Accept(scheduler.GetWorkerCount());
            scheduler.Join("any_group");
            CHECK(scheduler.IsJoined("any_group"));
            CHECK(!scheduler.IsJoined());
            CHECK_EQ(scheduler.GetTaskCount("any_group"), 0);
            CHECK_NE(scheduler.GetTaskCount(), 0);
            scheduler.Resume();
            scheduler.Join();
        }

        SUBCASE("task-auto-cancel")
        {
            scheduler.StartJoin();
            auto t1 = scheduler.Insert([] {}).AsUnique().Enqueue();
            CHECK_EQ(t1.GetState(), Hx::TaskState::Cancelled);
            scheduler.StopJoin();
            scheduler.StartJoin("any_group");
            auto t2 = scheduler.Insert([] {}).SetGroup("any_group").AsUnique().Enqueue();
            auto t3 = scheduler.Insert([] {}).AsUnique().Enqueue();
            CHECK_EQ(t2.GetState(), Hx::TaskState::Cancelled);
            CHECK_NE(t3.GetState(), Hx::TaskState::Cancelled);
            scheduler.StopJoin("any_group");
            scheduler.Join();
        }

        SUBCASE("task-cancel")
        {
            scheduler.Freeze();
            auto t1 = scheduler.Insert([] { return 1; }).AsUnique().Enqueue();
            t1.Cancel();
            scheduler.Resume();
            scheduler.Join();

            CHECK_EQ(t1.GetState(), Hx::TaskState::Cancelled);
        }

        SUBCASE("task-result")
        {
            auto t1 = scheduler.Insert([] { return 19; }).AsUnique().Enqueue();
            scheduler.Join();
            CHECK_EQ(t1.GetState(), Hx::TaskState::Done);
            CHECK_NE(t1.GetResult(), nullptr);
            CHECK_EQ(t1.GetResult()->get(), 19);
            CHECK_EQ(t1.GetResult(), nullptr);
        }

        SUBCASE("task-concurrent-result-access")
        {
            auto t1 = scheduler.Insert([] { return 19; })
                .AsShared()
                .Enqueue();

            for (int i = 0; i < 10; ++i)
            {
                scheduler.Insert([r1 = t1.GetResult()]() { r1.wait(); CHECK_EQ(r1.get(), 19); }).Enqueue();
            }
            scheduler.Join();
        }

        SUBCASE("task-execute")
        {
            scheduler.Freeze();
            for (size_t j = 0; j < scheduler.GetWorkerCount(); j++)
            {
                scheduler.Insert([] {}).Enqueue();
            }
            auto t1 = scheduler.Insert([] {}).SetGroup("any_group").AsUnique().Execute();
            scheduler.Accept();
            scheduler.Join("any_group");
            CHECK_EQ(scheduler.GetTaskCount(), scheduler.GetWorkerCount());
            CHECK_EQ(t1.GetState(), Hx::TaskState::Done);
            CHECK_EQ(scheduler.GetTaskCount("any_group"), 0);
            scheduler.Resume();
            scheduler.Join();
        }

        SUBCASE("task-param-binding")
        {
            auto fn = [](const int i, const int j) -> int { return i + j; };
            auto t1 = scheduler.Insert(fn, 1, 2).AsUnique().Enqueue();
            scheduler.Join();
            CHECK_EQ(t1.GetState(), Hx::TaskState::Done);
            CHECK_EQ(t1.GetResult()->get(), 3);
        }
    }
}