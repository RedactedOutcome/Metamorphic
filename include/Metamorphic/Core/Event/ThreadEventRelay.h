#pragma once

#include "pch.h"
#include "EventDispatcher.h"
#include "Core/Memory/DynamicBaseQueue.h"

/// @brief A class that collects events and polls them all on a certain thread. Does this with a queue so FIFO data structure.
class ThreadEventRelay{
public:
    ThreadEventRelay(EventDispatcher& dispatcher) noexcept : m_EventDispatcher(dispatcher){

    }
    /// @brief deallocates all queued events without freeing them. Must call HandleEvents() if you would like them to be handled
    ~ThreadEventRelay() noexcept{
        
    }

    /// @brief We pass as an rvalue so the data remains valid for when running it
    template<typename T>
    void Dispatch(T&& event) noexcept{
        static_assert(std::is_base_of<Event, T>::value, "ThreadEventRelay May not Dispatch an event that is not derived from Event");

        /// @brief we allocate some bytes that will be the new event and move all ownership to this new event

        /// @brief then we simple add it to our queued
        m_Mutex.lock();
        //m_QueuedEvents.emplace_back(eventData);
        m_EventQueue.Push(std::move(event));
        m_Mutex.unlock();
    }

    /// @brief Polls all incoming events. Must call on your desired thread
    void HandleEvents() noexcept{
        m_Mutex.lock();
        m_CopiedEventQueue = std::move(m_EventQueue);
        m_Mutex.unlock();
        
        while(m_CopiedEventQueue.GetQueueSize() > 0){
            Event* event = m_CopiedEventQueue.Pop();
            m_EventDispatcher.Dispatch((int)event->GetEventType(), *event);
        }
        
        m_CopiedEventQueue.Clear();
    }
public:
    DynamicBaseQueue<Event>& GetEventQueue()const noexcept {return (DynamicBaseQueue<Event>&)m_EventQueue;}
    DynamicBaseQueue<Event>& GetCopiedEventQueue()const noexcept {return (DynamicBaseQueue<Event>&)m_CopiedEventQueue;}
    EventDispatcher& GetEventDispatcher() const noexcept {return (EventDispatcher&)m_EventDispatcher;}
    std::mutex& GetMutex() const noexcept{return (std::mutex&)m_Mutex;}
private:
    DynamicBaseQueue<Event> m_EventQueue;
    DynamicBaseQueue<Event> m_CopiedEventQueue;
    EventDispatcher& m_EventDispatcher;
    std::mutex m_Mutex;
};