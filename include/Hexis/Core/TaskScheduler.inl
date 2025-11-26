//
// Created by Alex Clorennec on 05/08/2025.
//

namespace Hx
{

    template<typename T, typename F, typename... Args>
    TaskScheduler::Inserter<T, F, Args...>::Inserter(TaskScheduler& scheduler, F&& f, Args&&... args) :
        scheduler(scheduler),
        mTask(std::bind(std::forward<F>(f), std::forward<Args>(args)...)),
        mGroup(DefaultGroup)
    {}

    template<typename T, typename F, typename... Args>
    auto TaskScheduler::Inserter<T, F, Args...>::SetGroup(std::string group) -> Inserter&
    {
        mGroup = std::move(group);
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
        return scheduler.EnqueueTask(std::make_shared<Task<RType>>(std::move(mGroup), std::move(mTask)), T{});
    }

    template<typename T, typename F, typename... Args>
    auto TaskScheduler::Inserter<T, F, Args...>::Execute()
    {
        using RType = std::invoke_result_t<F, Args...>;
        return scheduler.ExecuteTask(std::make_shared<Task<RType>>(std::move(mGroup), std::move(mTask)), T{});
    }

    template<typename F, typename... Args>
    auto TaskScheduler::Insert(F&& f, Args&&... args) -> Inserter<AsNoneTag, F, Args...>
    {
        return Inserter<AsNoneTag, F, Args...>(*this, std::forward<F>(f), std::forward<Args>(args)...);
    }

    template<typename T>
    auto TaskScheduler::AddTaskInternal(std::shared_ptr<Task<T>>&& task, Action<T>&& action)
    {
        if (mJoining || mJoiningGroup.contains(task->GetGroup()))
        {
            task->Cancel();
            return task;
        }

        task->onCancel = [this, group = task->GetGroup()] {
            std::lock_guard lock(mMutex);
            --mTaskCountPerGroup[group];
            --mTaskCount;
        };

        std::unique_lock lock(mMutex);
        action(task);
        ++mTaskCount;
        ++mTaskCountPerGroup.try_emplace(task->GetGroup(), 0).first->second;
        lock.unlock();
        mCv.notify_one();

        return task;
    }

    template<typename T, typename A>
    auto TaskScheduler::EnqueueTask(std::shared_ptr<Task<T>>&& task, A)
    {
        return _::TagSpecified<A, T>(
            AddTaskInternal<T>(std::move(task), [this](auto ptr) { mTasks.emplace_back(std::move(ptr)); })
        );
    }

    template<typename T, typename A>
    auto TaskScheduler::ExecuteTask(std::shared_ptr<Task<T>>&& task, A)
    {
        return _::TagSpecified<A, T>(
            AddTaskInternal<T>(std::move(task), [this](auto ptr) { mTasks.emplace_front(std::move(ptr)); })
        );
    }


}
