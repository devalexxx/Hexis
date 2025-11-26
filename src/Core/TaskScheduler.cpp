//
// Created by Alex Clorennec on 05/08/2025.
//

#include "Hexis/Core/TaskScheduler.h"

#include <iostream>

namespace Hx
{

    TaskScheduler::TaskScheduler(const size_t workerCount) :
        mTaskCount(0),
        mActiveWorkerCount(0),
        mWorkerCount(workerCount),
        mJoining(false),
        mFrozen(false),
        mStop(false),
        mSteps(0)
    {
        for (size_t i = 0; i < mWorkerCount; i++)
        {
            mWorkers.emplace_back([this] {
                while (true)
                {
                    std::unique_lock lock(mMutex);
                    mCv.wait(lock, [this] { return (!mTasks.empty() && (!mFrozen || mSteps > 0)) || mStop; });
                    ++mActiveWorkerCount;
                    if (mStop)
                        return;
                    if (mFrozen)
                        mSteps--;

                    auto task  = std::move(mTasks.front());
                    auto group = task->GetGroup();
                    mTasks.pop_front();
                    lock.unlock();

                    if (task->Accept())
                    {
                        (*task)();
                        lock.lock();
                        --mTaskCountPerGroup[group];
                        --mTaskCount;
                    }

                    if (!lock.owns_lock())
                        lock.lock();
                    --mActiveWorkerCount;
                    lock.unlock();
                }
            });
        }
    }

    TaskScheduler::~TaskScheduler()
    {
        std::unique_lock lock(mMutex);
        mStop = true;
        lock.unlock();
        mCv.notify_all();
        for (auto& th: mWorkers) { th.join(); }
    }

    size_t TaskScheduler::GetWorkerCount() const
    {
        return mWorkerCount;
    }

    size_t TaskScheduler::GetActiveWorkerCount() const
    {
        return mActiveWorkerCount;
    }

    size_t TaskScheduler::GetTaskCount() const
    {
        return mTaskCount;
    }

    size_t TaskScheduler::GetTaskCount(const std::string& grp) const
    {
        if (const auto it = mTaskCountPerGroup.find(grp); it != mTaskCountPerGroup.end())
            return it->second;

        return 0;
    }

    void TaskScheduler::Freeze() const
    {
        if (!mFrozen)
        {
            std::unique_lock lock(mMutex);
            mFrozen = true;
            lock.unlock();
        }
    }

    void TaskScheduler::Resume() const
    {
        if (mFrozen)
        {
            std::unique_lock lock(mMutex);
            mFrozen = false;
            lock.unlock();
            mCv.notify_all();
        }
    }

    void TaskScheduler::Accept(const size_t steps) const
    {
        if (mFrozen)
        {
            std::unique_lock lock(mMutex);
            mSteps = steps;
            lock.unlock();
            mCv.notify_all();
        }
    }

    bool TaskScheduler::IsJoined() const
    {
        return mTaskCount == 0;
    }

    void TaskScheduler::StartJoin() const
    {
        std::lock_guard lock(mMutex);
        mJoining = true;
    }

    void TaskScheduler::StopJoin() const
    {
        std::lock_guard lock(mMutex);
        mJoining = false;
    }

    void TaskScheduler::Join() const
    {
        if (mJoining)
            return;

        StartJoin();
        while (!IsJoined()) {};
        StopJoin();
    }

    bool TaskScheduler::IsJoined(const std::string& grp) const
    {
        return GetTaskCount(grp) == 0;
    }

    void TaskScheduler::StartJoin(const std::string& grp) const
    {
        std::lock_guard lock(mMutex);
        mJoiningGroup.insert(grp);
    }

    void TaskScheduler::StopJoin(const std::string& grp) const
    {
        std::lock_guard lock(mMutex);
        mJoiningGroup.erase(grp);
    }

    void TaskScheduler::Join(const std::string& grp) const
    {
        if (IsJoined(grp))
            return;

        StartJoin(grp);
        while (!IsJoined(grp)) {};
        StopJoin(grp);
    }

    size_t TaskScheduler::GetThreadIndex()
    {
        static std::atomic<size_t> counter = 0;
        thread_local size_t        index   = counter++;
        return index;
    }

}