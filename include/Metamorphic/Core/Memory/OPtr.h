#pragma once

/// @brief A class that holds a pointer to type T but allows control of ownership manually or dynamically
/// @brief not a reference counted system
/// @tparam T 
template <typename T>
class OPtr{
public:
    OPtr() noexcept : m_Pointer(nullptr){}
    OPtr(T* pointer, bool hasOwnership = false) noexcept : m_Pointer(pointer), m_HasOwnership(hasOwnership){}
    OPtr(const OPtr<T>& ptr) noexcept : m_Pointer(m_Pointer), m_HasOwnership(false){}
    OPtr(OPtr<T>&& ptr) noexcept : m_Pointer(m_Pointer), m_HasOwnership(ptr.m_HasOwnership){
        ptr.m_Pointer = nullptr;
        ptr.m_HasOwnership = false;
    }
    ~OPtr()noexcept{
        if(!m_HasOwnership)return;
        delete m_Pointer;
    }

    void Free()noexcept{
        if(m_HasOwnership){
            delete m_Pointer;
        }
        m_HasOwnership = false;
        m_Pointer = nullptr;
    }

    void Release()noexcept{
        m_HasOwnership = false;
        m_Pointer = nullptr;
    }

    void Assign(T* pointer, bool hasOwnership) noexcept{
        Free();
        m_Pointer = pointer;
        m_HasOwnershipm_HasOwnership = hasOwnership;
    }

    T* operator->()noexcept{return m_Pointer;}
    explicit operator bool() const noexcept{
        return m_Pointer != nullptr;
    }
    OPtr<T>& operator=(const OPtr<T>& ptr)noexcept{
        Free();
        m_Pointer = ptr.m_Pointer;
        return *this;
    }
    OPtr<T>& operator=(OPtr<T>&& ptr)noexcept{
        Free();
        m_Pointer = ptr.m_Pointer;
        m_HasOwnership = ptr.m_HasOwnership;
        ptr.m_Pointer = nullptr;
        ptr.m_HasOwnership = false;
        return *this;
    }

    bool operator==(const OPtr<T>& right)noexcept{
        return m_Pointer == right.m_Pointer;
    }
private:
    T* m_Pointer = nullptr;
    bool m_HasOwnership = false;
};