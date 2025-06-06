#pragma once

#include "pch.h"


/// TODO: implement and actually make work/compile

struct HeapData{
    bool m_InUse = false;
    size_t m_UserDataSize = 0;
    void* m_Data = nullptr;
    HeapData* m_Next = nullptr;
};

template <typename T>
class TypeHeap{
public:
    TypeHeap()noexcept{
        m_Data = malloc(m_HeapSize);
        PushHeap(HeapData(false, 100,))
    }
    ~TypeHeap()noexcept{
        delete m_Data;
    }

    T* Allocate() noexcept{

    }

    void Free(T* ptr)noexcept{

    }
private:
    void PushHeap(HeadData data){
        m_HeapAt+=sizeof(data) + data.m_UserDataSize;
    }
private:
    void* m_Data = nullptr;
    size_t m_HeapSize = 12 * 1000;
    size_t m_HeapAt = 0;
};