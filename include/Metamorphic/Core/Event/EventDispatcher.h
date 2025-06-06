#pragma once

#include "pch.h"
#include "Event.h"

class EventDispatcher{
public:
    /// @brief we Dispatch an event of type t
    template<typename T>
    void Dispatch(T& event) noexcept{
        std::function<void(Event&)> callback = m_Callbacks[T::s_EventType];
        if(callback != nullptr)callback(event);
    }

    void Dispatch(int id, Event& event) noexcept{
        std::function<void(Event&)> callback = m_Callbacks[(EventType)id];
        if(callback != nullptr)callback(event);
    }

    template <typename EVENT>
    void AddDispatcher(std::function<void(EVENT&)> callback) noexcept{
        m_Callbacks[EVENT::s_EventType] = [callback](Event& e){
            callback(static_cast<EVENT&>(e));
        };
    }
private:
    std::unordered_map<EventType, std::function<void(Event&)>> m_Callbacks;
};