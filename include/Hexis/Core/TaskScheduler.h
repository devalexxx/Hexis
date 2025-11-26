//
// Created by Alex Clorennec on 05/08/2025.
//

#ifndef HX_CORE_TASK_SCHEDULER_H
#define HX_CORE_TASK_SCHEDULER_H

#include "Hexis/Core/Common.h"
#include "Hexis/Core/Task.h"
#include "Hexis/Core/Types.h"

#include <deque>
#include <string>
#include <thread>
#include <unordered_set>
#include <variant>

namespace Hx
{

    namespace _
    {
        template<typename, typename>
        struct TagSpecifier {};

        template<typename Tag, typename T>
        using TagSpecified = TagSpecifier<Tag, T>::Type;

        template<typename T>
        struct TagSpecifier<AsNoneTag, T>
        {
            using Type = void;
        };

        template<typename T>
        struct TagSpecifier<AsUniqueTag, T>
        {
            using Type = UniqueTaskRef<T>;
        };

        template<typename T>
        struct TagSpecifier<AsSharedTag, T>
        {
            using Type = SharedTaskRef<T>;
        };
    }

    inline constexpr std::string DefaultGroup = "default";

    class HX_CORE_API TaskScheduler
    {
      private:
        template<typename T, typename F, typename... Args>
        class Inserter;

      public:
        TaskScheduler(size_t workerCount = std::thread::hardware_concurrency());
        ~TaskScheduler();

        template<typename F, typename... Args>
        Inserter<AsNoneTag, F, Args...> Insert(F&& f, Args&&... args);

        size_t GetWorkerCount() const;
        size_t GetActiveWorkerCount() const;
        size_t GetTaskCount() const;
        size_t GetTaskCount(const std::string& grp) const;

        void Freeze() const;
        void Resume() const;
        void Accept(size_t steps = 1) const;

        bool IsJoined() const;
        void StartJoin() const;
        void StopJoin() const;
        void Join() const;

        bool IsJoined(const std::string& grp) const;
        void StartJoin(const std::string& grp) const;
        void StopJoin(const std::string& grp) const;
        void Join(const std::string& grp) const;

        static size_t GetThreadIndex();

      private:
        template<typename T>
        using Action = std::function<void(std::shared_ptr<Task<T>>)>;

        template<typename, typename F, typename... Args>
        class Inserter
        {
          public:
            Inserter(TaskScheduler& scheduler, F&& f, Args&&... args);

            Inserter& SetGroup(std::string group);

            Inserter<AsUniqueTag, F, Args...>& AsUnique();
            Inserter<AsSharedTag, F, Args...>& AsShared();

            auto Enqueue();
            auto Execute();

          private:
            TaskScheduler& scheduler;

            std::packaged_task<std::invoke_result_t<F, Args...>()> mTask;
            std::string                                            mGroup;
        };

        template<typename T>
        auto AddTaskInternal(std::shared_ptr<Task<T>>&& task, Action<T>&& action);
        template<typename T, typename A>
        auto EnqueueTask(std::shared_ptr<Task<T>>&& task, A);
        template<typename T, typename A>
        auto ExecuteTask(std::shared_ptr<Task<T>>&& task, A);

        std::deque<std::shared_ptr<TaskCallable>> mTasks;
        std::unordered_map<std::string, size_t>   mTaskCountPerGroup;
        size_t                                    mTaskCount;

        std::vector<std::thread> mWorkers;
        size_t                   mActiveWorkerCount;
        size_t                   mWorkerCount;

        mutable std::unordered_set<std::string> mJoiningGroup;
        mutable bool                            mJoining;
        mutable bool                            mFrozen;
        bool                                    mStop;
        mutable size_t                          mSteps;

        mutable std::condition_variable mCv;
        mutable std::mutex              mMutex;
    };

}

#include "Hexis/Core/TaskScheduler.inl"

#endif
