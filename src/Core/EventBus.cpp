// Copyright (c) 2025 devalexxx
// Distributed under the MIT License.
// https://opensource.org/licenses/MIT

#include "Hexis/Core/EventBus.h"

namespace Hx
{

    void EventBus::Poll()
    {
        for (; !mEventEmitterQueue.empty(); mEventEmitterQueue.pop())
        {
            auto evt = std::move(mEventEmitterQueue.front());
            evt(this);
        }
    }

}