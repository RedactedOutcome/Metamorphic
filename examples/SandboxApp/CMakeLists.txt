cmake_minimum_required(VERSION 3.19.2)
project("SandBoxApp")

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

file(GLOB SOURCES src/*.cpp)
add_executable(${CMAKE_PROJECT_NAME} ${SOURCES})

include(FetchContent)
FetchContent_Declare(
  Metamorphic
  SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../"
)
FetchContent_MakeAvailable(Metamorphic)
target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC Metamorphic)

# Run Commands
add_custom_target(run
  COMMAND ${CMAKE_PROJECT_NAME}
  COMMENT "Running ${CMAKE_PROJECT_NAME}"
  WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../"
)