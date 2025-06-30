#pragma once

namespace Metamorphic{
    class Heap{
    public:
        Heap()noexcept{

        }
    private:
        void* m_Data = nullptr;
        size_t m_Size = 0;
    };
}