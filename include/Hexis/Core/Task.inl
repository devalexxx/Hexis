//
// Created by Alex Clorennec on 19/11/2025.
//

namespace Hx
{

    template<typename T>
    Task<T>::Task(std::string group, std::packaged_task<T()> task) :
        mTask(std::move(task)),
        mState(TaskState::Planned),
        mGroup(std::move(group))
    {
        mFuture = mTask.get_future();
    }

    template<typename T>
    std::future<T>* Task<T>::GetResult()
    {
        std::lock_guard lock(mMutex);
        if (mFuture.valid())
            return &mFuture;

        return nullptr;
    }

    template<typename T>
    std::shared_future<T> Task<T>::GetSharedResult()
    {
        std::lock_guard lock(mMutex);
        if (mShared.valid())
            return mShared;

        return mShared = mFuture.share();
    }

    template<typename T>
    void Task<T>::Cancel()
    {
        std::lock_guard lock(mMutex);

        if (mState != TaskState::Planned)
            return;

        mState = TaskState::Cancelled;
        if (onCancel)
            onCancel();
    }

    template<typename T>
    bool Task<T>::Accept()
    {
        std::lock_guard lock(mMutex);
        if (mState != TaskState::Planned)
            return false;

        mState = TaskState::Accepted;
        return true;
    }

    template<typename T>
    void Task<T>::operator()()
    {
        std::unique_lock lock(mMutex);
        mState = TaskState::Running;
        lock.unlock();
        mTask();
        lock.lock();
        mState = TaskState::Done;
        lock.unlock();
    }

    template<typename T>
    TaskState Task<T>::GetState() const
    {
        return mState;
    }

    template<typename T>
    const std::string& Task<T>::GetGroup() const
    {
        return mGroup;
    }

    template<typename T>
    SharedTaskRef<T>::SharedTaskRef(std::shared_ptr<Task<T>> ref) : mRef(std::move(ref))
    {}

    template<typename T>
    std::shared_future<T> SharedTaskRef<T>::GetResult()
    {
        return mRef->GetSharedResult();
    }

    template<typename T>
    auto SharedTaskRef<T>::GetState() const -> TaskState
    {
        return mRef->GetState();
    }

    template<typename T>
    void SharedTaskRef<T>::Cancel()
    {
        mRef->Cancel();
    }

    template<typename T>
    UniqueTaskRef<T>::UniqueTaskRef(std::shared_ptr<Task<T>> ref) : mRef(std::move(ref))
    {}

    template<typename T>
    TaskState UniqueTaskRef<T>::GetState() const
    {
        return mRef->GetState();
    }

    template<typename T>
    std::future<T>* UniqueTaskRef<T>::GetResult()
    {
        return mRef->GetResult();
    }

    template<typename T>
    void UniqueTaskRef<T>::Cancel()
    {
        mRef->Cancel();
    }

}