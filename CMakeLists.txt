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
    set(MetamorphicLibraryType STATIC)
endif()
add_library(${PROJECT_NAME} ${MetamorphicLibraryType} ${SOURCES})

# Precompiled Headers
target_precompile_headers(${PROJECT_NAME} PRIVATE "include/Metamorphic/pch.h")

# Include Directories for Metamorphic
target_include_directories(${PROJECT_NAME} PUBLIC include/)
target_include_directories(${PROJECT_NAME} PRIVATE include/Metamorphic/)

# Platform Dependent Code
set(AdditionalSources "")
if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
    list(APPEND AdditionalSources Window/WindowsWindow.cpp)
    set(MetamorphicUseDirectX12 TRUE)
    set(MetamorphicUseOpenGL TRUE)
    set(MetamorphicGLEW TRUE)
    set(MetamorphicUseVulkan TRUE)
    set(MetamorhpicUsePhysX TRUE)
else()
    message(FATAL "Failed to get CMake Platform")
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
set(SPDLOG_NO_EXCEPTIONS ON CACHE BOOL "" FORCE)
set(SPDLOG_BUILD_STATIC ON)
FetchContent_Declare(
  spdlog
  SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libs/spdlog/"
)
FetchContent_MakeAvailable(spdlog)
target_compile_definitions(spdlog PUBLIC SPDLOG_NO_EXCEPTIONS)
target_link_libraries(${PROJECT_NAME} PUBLIC spdlog)

set(PlatformSrc src/Platform/)

# Rendering
if(${MetamorphicUseDirectX12})
    target_compile_definitions(${PROJECT_NAME} PUBLIC METAMORPHIC_USE_DIRECTX12)
endif()

if(${MetamorphicGLEW})
    target_compile_definitions(${PROJECT_NAME} PUBLIC METAMORPHIC_USE_GLEW GLEW_STATIC)
    target_include_directories(${PROJECT_NAME} PUBLIC libs/glew/include)
    target_link_directories(${PROJECT_NAME} PUBLIC libs/glew/lib/Release/x64)
    target_link_libraries(${PROJECT_NAME} PUBLIC glew32s.lib)
endif()

if(${MetamorphicUseOpenGL})
    target_link_libraries(${PROJECT_NAME} PUBLIC opengl32.lib)
    target_sources(${PROJECT_NAME} PRIVATE ${PlatformSrc}Renderers/OpenGLRenderer.cpp)
endif()

if(${MetamorphicUseVulkan})
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

# Appending src/platform/ to platform specific code
set(PlatformSpecificSources "")
foreach(file IN LISTS AdditionalSources)
    list(APPEND PlatformSpecificSources "src/Platform/${file}")
endforeach()
target_sources(${PROJECT_NAME} PRIVATE ${PlatformSpecificSources})