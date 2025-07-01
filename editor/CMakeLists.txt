cmake_minimum_required(VERSION 3.19.2)
set(M2D "Metamorphic-Editor-2D")
set(M3D "Metamorphic-Editor-3D")

# Metamorphic Engine
include(FetchContent)
FetchContent_Declare(
  Metamorphic
  SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../"
)
FetchContent_MakeAvailable(Metamorphic)

# 2D Editor
project(${M2D})

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

file(GLOB SOURCES src/*.cpp)
add_executable(${PROJECT_NAME} ${SOURCES})
target_compile_definitions(${PROJECT_NAME} PUBLIC METAMORPHIC_EDITOR METAMORPHIC_EDITOR_2D)

# Metamorphic Settings
set(MetamorphicGameType "2D")
set(MetamorphicNoPhysics TRUE)

target_link_libraries(${PROJECT_NAME} PUBLIC Metamorphic)

# 3D Editor
project(${M3D})

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

file(GLOB SOURCES src/*.cpp)
add_executable(${PROJECT_NAME} ${SOURCES})
target_compile_definitions(${PROJECT_NAME} PUBLIC METAMORPHIC_EDITOR METAMORPHIC_EDITOR_3D)

# Metamorphic Settings
set(MetamorphicGameType "3D")
set(MetamorphicNoPhysics TRUE)

target_link_libraries(${PROJECT_NAME} PUBLIC Metamorphic)

# Run Commands
add_custom_target(run2d
  COMMAND ${M2D}
  COMMENT "Running ${M2D}"
  WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../"
)
# Run Commands
add_custom_target(run3d
  COMMAND ${M3D}
  COMMENT "Running ${M3D}"
  WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../"
)