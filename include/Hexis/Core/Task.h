//
// Created by Alex Clorennec on 19/11/2025.
//

#ifndef HEXIS_CORE_TASK_H
#define HEXIS_CORE_TASK_H

#include "Hexis/Core/Common.h"

#include <functional>
#include <future>

namespace Hx
{

    enum class HX_CORE_API TaskState
    {
        Planned,
        Running,
        Done,
        Cancelled,
        Accepted,
    };

    template<typename T, typename... Args>
    struct Callable
    {
        virtual ~Callable()                = default;
        virtual T operator()(Args... args) = 0;
    };

    struct HX_CORE_API TaskCallable : Callable<void>
    {
        virtual const std::string& GetGroup() const = 0;
        virtual TaskState          GetState() const = 0;

        virtual uint32_t GetPriority() const        = 0;
        virtual void     SetPriority(uint32_t value) = 0;

        virtual bool Accept() = 0;
    };

    struct TaskCallableCompare
    {
        bool operator()(const std::shared_ptr<TaskCallable>& lhs, const std::shared_ptr<TaskCallable>& rhs) const
        {
            return std::less()(lhs->GetPriority(), rhs->GetPriority());
        }
    };

    template<typename T>
    class Task final : public TaskCallable
    {
      public:
        Task(std::string group, uint32_t priority, std::packaged_task<T()> task);

        void operator()() override;

        const std::string& GetGroup() const override;
        TaskState          GetState() const override;

        uint32_t GetPriority() const override;
        void     SetPriority(uint32_t value) override;

        std::future<T>*       GetResult();
        std::shared_future<T> GetSharedResult();

        void Cancel();
        bool Accept() override;

        std::function<void()> onCancel;

      private:
        std::packaged_task<T()> mTask;
        std::shared_future<T>   mShared;
        std::future<T>          mFuture;

        TaskState   mState;
        std::string mGroup;
        uint32_t    mPriority;
        std::mutex  mMutex;
    };

    struct HX_CORE_API AsUniqueTag {};
    struct HX_CORE_API AsSharedTag {};
    struct HX_CORE_API AsNoneTag   {};

    template<typename T>
    class UniqueTaskRef
    {
      public:
        UniqueTaskRef(std::shared_ptr<Task<T>> ref);

        std::future<T>* GetResult();
        TaskState       GetState() const;

        void Cancel();

      private:
        std::shared_ptr<Task<T>> mRef;
    };

    template<typename T>
    class SharedTaskRef
    {
      public:
        SharedTaskRef(std::shared_ptr<Task<T>> ref);

        std::shared_future<T> GetResult();
        TaskState             GetState() const;

        void Cancel();

      private:
        std::shared_ptr<Task<T>> mRef;
    };

}

#include "Hexis/Core/Task.inl"

#endif
