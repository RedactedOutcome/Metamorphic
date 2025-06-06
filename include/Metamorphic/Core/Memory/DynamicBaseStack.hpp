#pragma once

#include "pch.h"
#include "Core/Logger.h"

/// TODO: consider a stack type where we write our data then we append the sizeof that data

/// @brief an ascending heap allocated stack data structure where you can push and pop and type T where T is known at compile time and T is derived from base
template<typename Base, size_t DefaultStackSize=2000>
class DynamicBaseStack{
public:
    DynamicBaseStack() noexcept{
        m_StackSize = DefaultStackSize;
        m_StackData = malloc(m_StackSize);
    }
    ~DynamicBaseStack() noexcept{
        delete m_StackData;
    }

    DynamicBaseStack<Base, DefaultStackSize>& operator=(DynamicBaseStack<Base, DefaultStackSize>& right)=delete;
    DynamicBaseStack<Base, DefaultStackSize>& operator=(DynamicBaseStack<Base, DefaultStackSize>&& right) noexcept{
        delete m_StackData;
        m_StackData = right.m_StackData;
        right.m_StackData = nullptr;
        m_StackSize = right.m_StackSize;
        m_StackPointer = right.m_StackPointer;
        m_StackSizes = std::move(right.m_StackSizes);
        right.m_StackSize = 0;
        right.m_StackPointer = 0;
    }

    /// @brief sets the stack pointer and amount pushed at 0. Clears any stack sized. this way we can treat all of this data
    void Clear(){
        m_StackPointer = 0;
        m_AmountPushed = 0;
        m_StackSizes.clear();
    }
    /// @brief push T onto the stack and transfer ownership
    template <typename T>
    Base* Push(T& t) noexcept{
        static_assert(std::is_base_of<Base, T>::value, "Dynamic Base Stack Type T is not derived from type Base");
        
        size_t tSize = sizeof(T);
        T* current = static_cast<T*>(m_StackData + m_StackPointer);
        if(!m_StackData || m_StackPointer + tSize >= m_StackSize){
            /// Reallocate stack
            size_t newStackSize = std::min(DefaultStackSize, m_StackPointer + tSize);
            void* newStack = malloc(newStackSize);
            memcpy(newStack, m_StackData, m_StackSize);
            m_StackSize = newStackSize;
            delete m_StackData;
            m_StackData = newStack;
            current = static_cast<T*>(m_StackData + m_StackPointer);
        }
        new (current) T();

        *current = t;
        m_StackPointer+=tSize;
        m_StackSizes.emplace_back(tSize);
        
        return static_cast<Base*>(current);
    }

    /// @brief push T onto the stack and transfer ownership
    template <typename T>
    Base* Push(T&& t) noexcept{
        static_assert(std::is_base_of<Base, T>::value, "Dynamic Base Stack Type T is not derived from type Base");
        size_t tSize = sizeof(T);
        T* current = reinterpret_cast<T*>(static_cast<char*>(m_StackData) + m_StackPointer);
        if(!m_StackData || m_StackPointer + tSize >= m_StackSize){
            /// Reallocate stack
            size_t newStackSize = std::min(DefaultStackSize, m_StackPointer + tSize);
            void* newStack = malloc(newStackSize);
            memcpy(newStack, m_StackData, m_StackSize);
            m_StackSize = newStackSize;
            delete m_StackData;
            m_StackData = newStack;
            current = reinterpret_cast<T*>(static_cast<char*>(m_StackData) + m_StackPointer);
        }
        new (current) T();
        *current = std::move(t);
        m_StackPointer+=tSize;
        m_StackSizes.emplace_back(tSize);
        return static_cast<Base*>(current);
    }

    void Pop()noexcept{
        size_t stackSizes = m_StackSizes.size();
        if(stackSizes == 0)return;
        m_StackPointer -= m_StackSizes[stackSizes - 1];
        m_StackSizes.resize(stackSizes - 1);
    }

    Base* GetBaseAtStackPointer() const noexcept{
        return reinterpret_cast<Base*>((char*)m_StackData + m_StackPointer);
    }
public:
    void* GetStackData() const noexcept{return m_StackData;}
    size_t GetStackSize() const noexcept{return m_StackSize;}
    size_t GetStackPointer() const noexcept{return m_StackPointer;}
    size_t GetAmountPushed() const noexcept{return m_AmountPushed;}
    /// @brief returns a vector that contains all the sizes of all the items current pushed onto the stack
    std::vector<uint16_t>& GetStackSizes() const noexcept{return (std::vector<uint16_t>&)m_StackSizes;}
private:
    void* m_StackData = nullptr;
    /// @brief Size of stack in bytes
    size_t m_StackSize = 0;
    size_t m_StackPointer = 0;
    /// @brief the amount of data currently on the stack
    size_t m_AmountPushed=0;
    /// @brief Essentially another stack that contains the sizes of data pushed onto the stackdata
    std::vector<uint16_t> m_StackSizes;
};