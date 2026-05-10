// Copyright (c) 2025 devalexxx
// Distributed under the MIT License.
// https://opensource.org/licenses/MIT

#ifndef HEXIS_CORE_EVENT_BUS_H
#define HEXIS_CORE_EVENT_BUS_H

#include "Hexis/Core/Common.h"
#include "Hexis/Core/Types.h"

#include <queue>
#include <functional>

namespace Hx
{

    struct HX_CORE_API IEvent {};

    class EventBus;
    template<typename T>
    struct Event : IEvent
    {
        T event;
        void operator()(EventBus* bus);
    };

    template<typename>
    struct EventHandlerRef
    {
        i32 index;
    };

    class HX_CORE_API EventBus
    {
      public:
        template<typename T> void Emit   (T&& event);
        template<typename T> void Emit   (Event<T> event);
        template<typename T> void Enqueue(T&& event);

        template<typename T, typename F, typename... Args>
        EventHandlerRef<T> Subscribe(F&& f, Args&&... args);
        template<typename T>
        void Withdraw(EventHandlerRef<T> ref);

        void Poll();

      private:
        using EventEmitter = std::function<void(EventBus*)>;
        template<typename T> using  EventHandler = std::function<void(const T&)>;
        template<typename T> struct EventHandlerCollection
        {
            std::vector<EventHandler<T>> handlers;
            void operator()(const IEvent& event);
        };

        std::unordered_map<i64, EventHandler<IEvent>> mEventHandlerMap;
        std::queue<EventEmitter>                      mEventEmitterQueue; // TODO: use concurrent queue
    };

}

#include "Hexis/Core/EventBus.inl"

#endif
