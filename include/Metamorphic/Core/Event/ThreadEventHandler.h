#pragma once

#include "pch.h"

/// @brief class that runs events dedicated for a certain thread
class ThreadEventHandler{
public:
    ThreadEventHandler() noexcept;
    ~ThreadEventHandler() noexcept;

    /// @brief Handles all queued events
    void HandleEvents()noexcept;
    void AddEvent(std::function<void()> event) noexcept;
public:
    std::vector<std::function<void()>>& GetEvents(){return (std::vector<std::function<void()>>&)m_Events;}
    std::vector<std::function<void()>>& GetCopyVector(){return (std::vector<std::function<void()>>&)m_CopyVector;}
private:
    std::vector<std::function<void()>> m_Events;
    std::vector<std::function<void()>> m_CopyVector;
    std::mutex m_Mutex;
};