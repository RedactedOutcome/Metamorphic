#pragma once

#include "Metamorphic/pch.h"
#include "Resources.h"

namespace Metamorphic{
    enum class ResourceManagerError{
        None=0,
        FileNotFound,
        AccessDenied,
        FileIsLocked,
        FileIsDirectory,
        TooManyOpenFiles,
        DiskFull,
        ReadOnlyFileSystem,
        InvalidPath,
        FileNameTooLong,
        FileExists,
        DeviceError,
        SymlinkLoop,
        FileSystemCorrupted,
        UnsupportedOperation,
        UnsupportedAPI
    };

    class ResourceManager{
    public:
        static ResourceManagerError LoadResource(ResourceType type, const std::filesystem::path& path, HBuffer& output)noexcept;
    };
}