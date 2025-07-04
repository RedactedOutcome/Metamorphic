#pragma once


namespace Metamorphic{
    enum class BufferUsage{
        None=0
    };
    enum class BufferDataType{
        Float = 0,
        UInt8,
        Int8,
        UInt16,
        Int16,
        UInt32,
        Int32
    };
    struct BufferCreateData{
        BufferDataType m_Type;
        BufferUsage m_Usage;
        size_t size;
    };
}