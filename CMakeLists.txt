cmake_minimum_required(VERSION 3.19.2)
project("Metamorphic")

file(GLOB_RECURSE SOURCES src/*.cpp)

set(METAMORPHIC_LIBRARY_TYPE STATIC)
add_library(${PROJECT_NAME} ${METAMORPHIC_LIBRARY_TYPE} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC include/)
target_include_directories(${PROJECT_NAME} PRIVATE include/Metamorphic/)