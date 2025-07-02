cmake_minimum_required(VERSION 3.19.2)
project("Metamorphic")

# Engine does not support x32 architectures

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

# Get Metamorphic Core Engine Files
file(GLOB_RECURSE SOURCES src/*.cpp)
foreach(file ${SOURCES})
    if(file MATCHES "src/Platform/")
        list(REMOVE_ITEM SOURCES ${file})
    endif()
endforeach()

if(NOT DEFINED MetamorphicLibraryType)
    set(MetamorphicLibraryType "STATIC")
endif()

add_library(${PROJECT_NAME} ${MetamorphicLibraryType} ${SOURCES})

if("${MetamorphicLibraryType}" STREQUAL "DYNAMIC")
    target_compile_definitions(${PROJECT_NAME} PRIVATE METAMORPHIC_EXPORTS)
elseif("${MetamorphicLibraryType}" STREQUAL "STATIC")
    target_compile_definitions(${PROJECT_NAME} PUBLIC METAMORPHIC_STATIC)
else()
    message(FATAL "Metamorphic Unsupported Type ${MetamorphicLibraryType}")
endif()

# Precompiled Headers
target_precompile_headers(${PROJECT_NAME} PRIVATE "include/Metamorphic/pch.h")

# Include Directories for Metamorphic
target_include_directories(${PROJECT_NAME} PUBLIC include/)
target_include_directories(${PROJECT_NAME} PRIVATE include/Metamorphic/)

# Release Type
if(NOT DEFINED MetamorphicReleaseType OR MetamorphicReleaseType STREQUAL "Release")
    target_compile_definitions(${PROJECT_NAME} PUBLIC METAMORPHIC_RELEASE)
elseif(${MetamorphicReleaseType} STREQUAL "Dist")
    target_compile_definitions(${PROJECT_NAME} PUBLIC METAMORPHIC_DIST)
else()
    message(FATAL "Unsupported Metamorphic Release Type: ${MetamorphicReleaseType}")
endif()
# Platform Dependent Code
set(AdditionalSources "")

if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
    target_compile_definitions(${PROJECT_NAME} PUBLIC UNICODE _UNICODE METAMORPHIC_PLATFORM_WINDOWS _WIN32_WINNT_WIN10 _WIN32_WINNT=0x0A0000 NTDDI_VERSION=0x0A000000)
    list(APPEND AdditionalSources Window/WindowsWindow.cpp)
    set(MetamorphicUseDirectX12 TRUE)
    set(MetamorphicUseOpenGL TRUE)
    set(MetamorphicGLEW TRUE)
    set(MetamorphicUseVulkan TRUE)
    set(MetamorhpicUsePhysX TRUE)
    set(MetamorphicUseOpenAL TRUE)
    set(MetamorphicUseSpdlog TRUE)
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Android")
    message(FATAL "Android Not Supported Yet")
else()
    message(FATAL "Failed to get supported Metamorphic CMake Platform")
endif()

if(NOT DEFINED MetamorphicGameType)
    message(FATAL "No Metamorphic game type specified. May either be 2D or 3D.")
else()
    if(${MetamorphicGameType} STREQUAL "3D")
        target_compile_definitions(${PROJECT_NAME} PUBLIC METAMORPHIC_3D_GAME)
    elseif(${MetamorphicGameType} STREQUAL "2D")
        target_compile_definitions(${PROJECT_NAME} PUBLIC METAMORPHIC_2D_GAME)
    else()
        message(FATAL "Unsupported Metamorphic game type specified")
    endif()
endif()

# Memory Management
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/libs/HBuffer/include)

# Math
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/libs/sfmath")
target_link_libraries(${PROJECT_NAME} PUBLIC sfmath)

# Logging
if(DEFINED MetamorphicUseSpdlog)
    target_compile_definitions(${PROJECT_NAME} PUBLIC METAMORPHIC_USE_SPDLOG)
    set(SPDLOG_NO_EXCEPTIONS ON CACHE BOOL "" FORCE)
    set(SPDLOG_BUILD_STATIC ON)
    FetchContent_Declare(
    spdlog
    SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libs/spdlog/"
    )
    FetchContent_MakeAvailable(spdlog)
    target_compile_definitions(spdlog PUBLIC SPDLOG_NO_EXCEPTIONS)
    target_link_libraries(${PROJECT_NAME} PUBLIC spdlog)
endif()

set(PlatformSrc src/Platform/)

# Rendering
if(${MetamorphicUseDirectX12})
    target_compile_definitions(${PROJECT_NAME} PUBLIC METAMORPHIC_USE_DIRECTX12)
    target_sources(${PROJECT_NAME} PRIVATE ${PlatformSrc}Renderers/DirectX12Renderer.cpp)
endif()

if(${MetamorphicGLEW})
    target_compile_definitions(${PROJECT_NAME} PUBLIC METAMORPHIC_USE_GLEW GLEW_STATIC)
    target_include_directories(${PROJECT_NAME} PUBLIC libs/glew/include)
    target_link_directories(${PROJECT_NAME} PUBLIC libs/glew/lib/Release/x64)
    target_link_libraries(${PROJECT_NAME} PUBLIC glew32s.lib)
endif()

if(${MetamorphicUseOpenGL})
    if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
        target_link_libraries(${PROJECT_NAME} PUBLIC opengl32.lib)
    elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Android")
        message(FATAL "Android Not Supported Yet")
    else()
        message(FATAL "Metamorphic OpenGL Unsupported platform ${CMAKE_SYSTEM_NAME}")
    endif()

    target_sources(${PROJECT_NAME} PRIVATE ${PlatformSrc}Renderers/OpenGLRenderer.cpp)
endif()

if(${MetamorphicUseVulkan})
    if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
        target_compile_definitions(${PROJECT_NAME} PUBLIC VK_USE_PLATFORM_WIN32_KHR)
    else()
        message(FATAL "Metamorphic Vulkan unsupported platform")
    endif()
    target_sources(${PROJECT_NAME} PRIVATE ${PlatformSrc}Renderers/VulkanRenderer.cpp)
    target_compile_definitions(${PROJECT_NAME} PUBLIC METAMORPHIC_USE_VULKAN)
    target_include_directories(${PROJECT_NAME} PUBLIC $ENV{VULKAN_SDK}/Include)
    target_link_directories(${PROJECT_NAME} PUBLIC $ENV{VULKAN_SDK}/Lib)
    target_link_libraries(${PROJECT_NAME} PUBLIC vulkan-1.lib)
endif()

# Physics
if(${MetamorphicNoPhysics})
    target_compile_definitions(${PROJECT_NAME} PUBLIC METAMORPHIC_NO_PHYSICS_ENGINE)
else()
    if(${MetamorhpicUsePhysX})
        target_compile_definitions(${PROJECT_NAME} PUBLIC METAMORPHIC_USE_PHYSX)
        set(PHYSX_ROOT_DIR $ENV{PHYSX_ROOT_DIR})
        set(PX_OUTPUT_LIB_DIR "${CMAKE_BINARY_DIR}/lib" CACHE PATH "PhysX output lib directory")
        set(PX_OUTPUT_BIN_DIR "${CMAKE_BINARY_DIR}/bin" CACHE PATH "PhysX output binary directory")
        string(REPLACE "\\" "/" PHYSX_PATH "$ENV{PHYSX_ROOT_DIR}")
        set(PHYSX_GENERATE_STATIC_LIBRARIES ON)
        FetchContent_Declare(
            PhysXSDK
            SOURCE_DIR "${PHYSX_PATH}/compiler/public"
            )
        FetchContent_MakeAvailable(PhysXSDK)
        target_link_libraries(${PROJECT_NAME} PUBLIC PhysXSDK)
    endif()
endif()

# Sounds
if(${MetamorphicUseOpenAL})
    target_compile_definitions(${PROJECT_NAME} PUBLIC METAMORPHIC_USE_OPENAL)
    add_subdirectory(libs/openal-soft)
    target_link_libraries(${PROJECT_NAME} PUBLIC OpenAL)
else()
    message(FATAL "Metamorphic No Sound API Specified")
endif()

# Appending src/platform/ to platform specific code
set(PlatformSpecificSources "")
foreach(file IN LISTS AdditionalSources)
    list(APPEND PlatformSpecificSources "src/Platform/${file}")
endforeach()
target_sources(${PROJECT_NAME} PRIVATE ${PlatformSpecificSources})