//
// Created by Alex Clorennec on 05/08/2025.
//

#ifndef HX_CORE_THREAD_POOL_H
#define HX_CORE_THREAD_POOL_H

#include <functional>
#include <future>
#include <queue>
#include <thread>

namespace Hx
{

	class ThreadPool
	{
		public:
			explicit ThreadPool(size_t threadCount = std::thread::hardware_concurrency());
			~ThreadPool();

			template<typename F, typename... Args>
			auto ExecuteTask(F&& f, Args&&... args) -> std::future<decltype(f(args...))>;


		private:
			size_t mThreadCount;
			std::vector<std::thread> mThreads;
			std::queue<std::function<void()>> mTasks;
			std::mutex mMutex;
			std::condition_variable mCv;
			bool mStop;
	};

}

#include "Hexis/Core/ThreadPool.inl"

#endif
