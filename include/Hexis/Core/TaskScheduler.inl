//
// Created by Alex Clorennec on 05/08/2025.
//

#include <algorithm>
#include <iostream>

namespace Hx
{

    template<typename T, typename F, typename... Args>
    TaskScheduler::Inserter<T, F, Args...>::Inserter(TaskScheduler& scheduler, F&& f, Args&&... args) :
        scheduler(scheduler),
        mTask(std::bind(std::forward<F>(f), std::forward<Args>(args)...)),
        mGroup(DefaultGroup),
        mPriority(0)
    {}

    template<typename T, typename F, typename... Args>
    auto TaskScheduler::Inserter<T, F, Args...>::SetGroup(std::string group) -> Inserter&
    {
        mGroup = std::move(group);
        return *this;
    }

    template<typename T0, typename F, typename... Args>
    auto TaskScheduler::Inserter<T0, F, Args...>::SetPriority(const uint32_t priority) -> Inserter&
    {
        mPriority = std::min(MaxPriority, priority);
        return *this;
    }

    template<typename T, typename F, typename... Args>
    auto TaskScheduler::Inserter<T, F, Args...>::AsUnique() -> Inserter<AsUniqueTag, F, Args...>&
    {
        return *reinterpret_cast<Inserter<AsUniqueTag, F, Args...>*>(this);
    }

    template<typename T, typename F, typename... Args>
    auto TaskScheduler::Inserter<T, F, Args...>::AsShared() -> Inserter<AsSharedTag, F, Args...>&
    {
        return *reinterpret_cast<Inserter<AsSharedTag, F, Args...>*>(this);
    }

    template<typename T, typename F, typename... Args>
    auto TaskScheduler::Inserter<T, F, Args...>::Enqueue()
    {
        using RType = std::invoke_result_t<F, Args...>;
        return scheduler.EnqueueTask(std::make_shared<Task<RType>>(std::move(mGroup), mPriority, std::move(mTask)), T{});
    }

    template<typename T, typename F, typename... Args>
    auto TaskScheduler::Inserter<T, F, Args...>::Execute()
    {
        using RType = std::invoke_result_t<F, Args...>;
        return scheduler.ExecuteTask(std::make_shared<Task<RType>>(std::move(mGroup), mPriority, std::move(mTask)), T{});
    }

    template<typename F, typename... Args>
    auto TaskScheduler::Insert(F&& f, Args&&... args) -> Inserter<AsNoneTag, F, Args...>
    {
        return Inserter<AsNoneTag, F, Args...>(*this, std::forward<F>(f), std::forward<Args>(args)...);
    }

    template<typename T>
    auto TaskScheduler::AddTaskInternal(std::shared_ptr<Task<T>>&& task)
    {
        if (mJoining || mJoiningGroup.contains(task->GetGroup()))
        {
            task->Cancel();
            return task;
        }

        task->onCancel = [this, group = task->GetGroup()] {
            std::lock_guard lock(mMutex);
            --mTaskCountPerGroup[group];
            mTaskCount = mTaskCount - 1;
        };

        std::unique_lock lock(mMutex);
        mTasks.push(task);
        mTaskCount = mTaskCount + 1;
        ++mTaskCountPerGroup.try_emplace(task->GetGroup(), 0).first->second;
        lock.unlock();
        mCv.notify_one();

        return task;
    }

    template<typename T, typename A>
    auto TaskScheduler::EnqueueTask(std::shared_ptr<Task<T>>&& task, A)
    {
        return _::TagSpecified<A, T>(AddTaskInternal<T>(std::move(task)));
    }

    template<typename T, typename A>
    auto TaskScheduler::ExecuteTask(std::shared_ptr<Task<T>>&& task, A)
    {
        if (const auto top = mTasks.top(); top) task->SetPriority(std::max(top->GetPriority() + 1, MaxPriority + 1));
        else                                    task->SetPriority(MaxPriority + 1);
        return _::TagSpecified<A, T>(AddTaskInternal<T>(std::move(task)));
    }

}
