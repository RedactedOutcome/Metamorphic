#pragma once

#include "pch.h"

/// @brief a FIFO queue implementation where you can push any class that derived from Base or Base and pop it
/// @brief class is not multithreaded. Dont rely on pointers always being valid especially after pushing onto the queue incase there is need for a resize
/// @param DefaultQueueSize the default size that the queue will be in bytes
/// TODO: potential custom allocator as a typename
template<typename Base, size_t DefaultQueueSize=sizeof(Base)*20>
class DynamicBaseQueue{
public:
    DynamicBaseQueue() noexcept{
        m_BufferSize = DefaultQueueSize;
        m_Buffer = malloc(m_BufferSize);
    }
    ~DynamicBaseQueue() noexcept{
        delete m_Buffer;
    }

    DynamicBaseQueue<Base, DefaultQueueSize>& operator=(DynamicBaseQueue<Base, DefaultQueueSize>& right)=delete;
    DynamicBaseQueue<Base, DefaultQueueSize>& operator=(DynamicBaseQueue<Base, DefaultQueueSize>&& right) noexcept{
        delete m_Buffer;
        m_Buffer = right.m_Buffer;
        m_BufferSize = right.m_BufferSize;

        right.m_Buffer = nullptr;
        right.m_BufferSize = 0;

        m_QueuePushOffset = right.m_QueuePushOffset;
        m_QueuePopOffset = right.m_QueuePopOffset;
        m_QueueSizes = std::move(right.m_QueueSizes);
        right.m_QueuePushOffset = 0;
        right.m_QueuePopOffset = 0;
    }

    /// @brief sets the stack pointer and amount pushed at 0. Clears any stack sized. this way we can treat all of this data
    void Clear(){
        m_QueuePushOffset = 0;
        m_QueuePopOffset = 0;
        m_QueueSizes.clear();
    }

    /// @brief push T onto the stack and transfer ownership
    template <typename T>
    Base* Push(T& t) noexcept{
        static_assert(std::is_base_of<Base, T>::value, "Dynamic Base Queue Type T is not derived from type Base");

        size_t typeSize = sizeof(T);
        T* current = nullptr;
        size_t endPushOffset = m_QueuePushOffset + typeSize;

        /// I prefer the switch statement enclosing this rather than if statement
        switch(static_cast<uint8_t>(m_LoopedAround)){
        case 1:{
            if(endPushOffset >= m_QueuePopOffset){
                /// @brief reallocate
                size_t newSize = m_BufferSize + typeSize;
                /// @brief the amount in the buffer "remaining" aka just the remaining bytes that contain pushed data
                char* buffer = new char[newSize];
                memcpy(buffer, reinterpret_cast<char*>(m_Buffer), m_QueuePushOffset);
                memcpy(buffer + endPushOffset, reinterpret_cast<char*>(m_Buffer) + m_QueuePopOffset, m_PopDataSize);
                m_QueuePopOffset = endPushOffset;
                m_BufferSize = newSize;
                m_Buffer = reinterpret_cast<void*>(buffer);
            }
            current = reinterpret_cast<T*>(reinterpret_cast<char*>(m_Buffer) + m_QueuePushOffset);
            m_QueuePushOffset = endPushOffset;
            break;
        }
        default:{
            if(endPushOffset <= m_BufferSize){
                current = reinterpret_cast<T*>(reinterpret_cast<char*>(m_Buffer) + m_QueuePushOffset);
                m_QueuePushOffset = endPushOffset;
                m_PopDataSize += typeSize;
                break;
            }
            /// Loop Around
            m_LoopedAround = 1;
            m_QueuePushOffset = 0;
            return Push<T>(std::move(t));
        }
        }

        /// @brief initialize vtable and ect
        new (current) T();
        *current = t;
        m_QueueSizes.emplace_back(static_cast<uint16_t>(typeSize));
        return static_cast<Base*>(current);
    }
    
    /// @brief push T onto the stack and transfer ownership
    template <typename T>
    Base* Push(T&& t) noexcept{
        static_assert(std::is_base_of<Base, T>::value, "Dynamic Base Queue Type T is not derived from type Base");

        size_t typeSize = sizeof(T);
        T* current = nullptr;
        size_t endPushOffset = m_QueuePushOffset + typeSize;

        /// I prefer the switch statement enclosing this rather than if statement
        switch(static_cast<uint8_t>(m_LoopedAround)){
        case 1:{
            if(endPushOffset >= m_QueuePopOffset){
                /// @brief reallocate
                size_t newSize = m_BufferSize + typeSize;
                /// @brief the amount in the buffer "remaining" aka just the remaining bytes that contain pushed data
                char* buffer = new char[newSize];
                memcpy(buffer, reinterpret_cast<char*>(m_Buffer), m_QueuePushOffset);
                memcpy(buffer + endPushOffset, reinterpret_cast<char*>(m_Buffer) + m_QueuePopOffset, m_PopDataSize);
                m_QueuePopOffset = endPushOffset;
                m_BufferSize = newSize;
                m_Buffer = reinterpret_cast<void*>(buffer);
            }
            current = reinterpret_cast<T*>(reinterpret_cast<char*>(m_Buffer) + m_QueuePushOffset);
            m_QueuePushOffset = endPushOffset;
            break;
        }
        default:{
            if(endPushOffset <= m_BufferSize){
                current = reinterpret_cast<T*>(reinterpret_cast<char*>(m_Buffer) + m_QueuePushOffset);
                m_QueuePushOffset = endPushOffset;
                m_PopDataSize += typeSize;
                break;
            }
            /// Loop Around
            m_LoopedAround = 1;
            m_QueuePushOffset = 0;
            return Push<T>(std::move(t));
        }
        }

        /// @brief initialize vtable and ect
        new (current) T();
        *current = std::move(t);
        m_QueueSizes.emplace_back(static_cast<uint16_t>(typeSize));
        return static_cast<Base*>(current);
    }

    Base* Pop()noexcept{
        if(GetQueueSize() < 1)return nullptr;
        size_t typeSize = static_cast<size_t>(m_QueueSizes[0]);
        size_t endPopSize = m_QueuePopOffset + typeSize;
        Base* returnValue = nullptr;
        if(endPopSize >= m_BufferSize){
            m_LoopedAround = 0;
            m_QueuePopOffset = 0;
            m_PopDataSize = 0;
        }

        returnValue = reinterpret_cast<Base*>(reinterpret_cast<char*>(m_Buffer) + m_QueuePopOffset);
        m_QueuePopOffset += typeSize;
        m_QueueSizes.erase(m_QueueSizes.begin());
        return returnValue;
    }
public:
    /// @brief returns the queue buffer
    void* GetData() const noexcept{return m_Buffer;}
    /// @brief returns the amount of bytes the queue buffer is
    size_t GetSize() const noexcept{return m_BufferSize;}
    /// @brief returns the amount of items currently pushed onto the queue
    size_t GetQueueSize() const noexcept{return m_QueueSizes.size();}
    //// @brief returns where in the queue buffer we are reading and writing this memory from
    size_t GetQueuePointer() const noexcept{return m_QueuePointer;}

    size_t GetPopQueueSize() noexcept{
        if(GetQueueSize() < 1)return 0;
        return static_cast<size_t>(m_QueueSizes[0]);
    }
private:
    void* m_Buffer = nullptr;
    /// @brief Size of data in bytes
    size_t m_BufferSize = 0;
    /// @brief The position in the queue buffer that we are pushing data onto
    size_t m_QueuePushOffset = 0;
    /// @brief The positin in the queue buffer that we are popping data from
    size_t m_QueuePopOffset = 0;
    /// @brief the amount of contiguous data at m_QueuePopOffset that we have until we are either out of queue data or reached the end of the buffer
    size_t m_PopDataSize=0;
    /// @brief the status on how the m_QueuePushOffset is looped around the circular queue buffer
    bool m_LoopedAround = 0;
    /// @brief the size of the type that was last pushed onto the queue. Used for resizing the buffer when circular buffer overlaps
    std::vector<uint16_t> m_QueueSizes;
};