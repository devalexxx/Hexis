// Copyright (c) 2025 devalexxx
// Distributed under the MIT License.
// https://opensource.org/licenses/MIT

#include "Hexis/Core/Hash.h"

namespace Hx
{

    template<typename T>
    void Event<T>::operator()(EventBus* bus)
    {
        bus->Emit(std::move(*this));
    }

    template<typename T>
    void EventBus::Emit(T&& event)
    {
        Emit(Event<T> { .event = std::forward<T>(event) });
    }

    template<typename T>
    void EventBus::Emit(Event<T> event)
    {
        auto hash = Hash<Type<T>, FNV1a64>{}();

        if (!mEventHandlerMap.contains(hash))
            mEventHandlerMap[hash] = EventHandlerCollection<T> {};

        mEventHandlerMap[hash].operator()(std::move(event));
    }

    template<typename T>
    void EventBus::Enqueue(T&& event)
    {
        auto hash = Hash<Type<T>, FNV1a64>{}();
        if (!mEventHandlerMap.contains(hash))
            mEventHandlerMap[hash] = EventHandlerCollection<T> {};

        mEventEmitterQueue.push(Event<T> { .event = std::forward<T>(event) });
    }

    template<typename T, typename F, typename... Args>
    EventHandlerRef<T> EventBus::Subscribe(F&& f, Args&&... args)
    {
        auto hash  = Hash<Type<T>, FNV1a64>{}();
        auto bound = std::bind(std::forward<F>(f), std::placeholders::_1, std::forward<Args>(args)...);

        if (!mEventHandlerMap.contains(hash))
            mEventHandlerMap[hash] = EventHandlerCollection<T> {};

        auto& handlers = mEventHandlerMap[hash].template target<EventHandlerCollection<T>>()->handlers;
        i32   index    = -1;
        for (u32 i = 0; i < handlers.size(); ++i)
        {
            if (!handlers[i])
            {
                handlers[i] = std::move(bound);
                index       = i;
                break;
            }
        }

        if (index == -1)
        {
            handlers.push_back(std::move(bound));
            index = handlers.size() - 1;
        }

        return EventHandlerRef<T> { index };
    }

    template<typename T>
    void EventBus::Withdraw(EventHandlerRef<T> ref)
    {
        if (ref.index < 0)
            return;

        auto hash = Hash<Type<T>, FNV1a64>{}();
        if (!mEventHandlerMap.contains(hash))
            return;

        auto& handlers = mEventHandlerMap[hash].template target<EventHandlerCollection<T>>()->handlers;
        if (ref.index >= handlers.size())
            return;

        handlers[ref.index] = {};
    }

    template<typename T>
    void EventBus::EventHandlerCollection<T>::operator()(const IEvent& event)
    {
        auto& evt = static_cast<const Event<T>&>(event).event;
        for (auto& handler : handlers)
        {
            if (handler)
                handler(evt);
        }
    }


}