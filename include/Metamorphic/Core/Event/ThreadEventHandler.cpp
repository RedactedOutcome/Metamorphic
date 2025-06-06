#include "pch.h"
#include "ThreadEventHandler.h"

ThreadEventHandler::ThreadEventHandler()noexcept{}
ThreadEventHandler::~ThreadEventHandler()noexcept{}

void ThreadEventHandler::HandleEvents() noexcept{
    m_CopyVector.resize(0);
    m_Mutex.lock();
    m_CopyVector.reserve(m_Events.size());
    for(size_t i = 0; i < m_Events.size(); i++){
        m_CopyVector.emplace_back(std::move(m_Events[i]));
    }
    m_Events.clear();
    m_Mutex.unlock();

    for(size_t i = 0; i < m_CopyVector.size(); i++){
        m_CopyVector[i]();
    }
}
void ThreadEventHandler::AddEvent(std::function<void()> event) noexcept{
    m_Mutex.lock();
    m_Events.push_back(event);
    m_Mutex.unlock();
}