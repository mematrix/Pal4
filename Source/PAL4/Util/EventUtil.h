#pragma once

#include <utility>

#include <Platform.h>

template<typename Event, typename... Args>
FORCEINLINE void InvokeEvent(Event& e, Args&&... args)
{
    if (e.IsBound())
    {
        e.Broadcast(std::forward<Args>(args)...);
    }
}

