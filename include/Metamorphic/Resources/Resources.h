#pragma once

namespace Metamorphic{
    enum class ResourceLoadError{
        None=0,
        FailedToOpenFile,
        FileDoesntExist,
        ResourceLocked
    };
}