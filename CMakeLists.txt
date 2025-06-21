cmake_minimum_required(VERSION 3.19.2)
project("Metamorphic")

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

# Get Metamorphic Core Engine Files
file(GLOB_RECURSE SOURCES src/*.cpp)
foreach(file ${SOURCES})
    if(file MATCHES "/src/platform/")
        list(REMOVE_ITEM SOURCES ${file})
    endif()
endforeach()

set(METAMORPHIC_LIBRARY_TYPE STATIC)
add_library(${PROJECT_NAME} ${METAMORPHIC_LIBRARY_TYPE} ${SOURCES})

# Precompiled Headers
target_precompile_headers(${PROJECT_NAME} PRIVATE "include/Metamorphic/pch.h")

# Include Directories for Metamorphic
target_include_directories(${PROJECT_NAME} PUBLIC include/)
target_include_directories(${PROJECT_NAME} PRIVATE include/Metamorphic/)

# Platform Dependent Code
set(AdditionalSources "")
if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
    list(APPEND AdditionalSources Window/WindowsWindow.cpp)
    set(MetamorphicGLEW TRUE)
    set(MetamorphicUseOpenGL TRUE)
else()
message(FATAL "Failed to get CMake Platform")
endif()

# Appending src/platform/
set(PlatformSpecificSources "")
foreach(file IN LISTS AdditionalSources)
    list(APPEND PlatformSpecificSources "src/platform/${file}")
endforeach()
target_sources(${PROJECT_NAME} PRIVATE ${PlatformSpecificSources})

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

# Rendering
if(${MetamorphicGLEW})
    target_compile_definitions(${PROJECT_NAME} PUBLIC METAMORPHIC_USE_GLEW GLEW_STATIC)
    target_include_directories(${PROJECT_NAME} PUBLIC libs/glew/include)
    target_link_directories(${PROJECT_NAME} PUBLIC libs/glew/lib/Release/x64)
    target_link_libraries(${PROJECT_NAME} PUBLIC glew32s.lib)
endif()
if(${MetamorphicUseOpenGL})
    target_link_libraries(${PROJECT_NAME} PUBLIC opengl32.lib)
endif()