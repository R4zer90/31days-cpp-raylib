cmake_minimum_required(VERSION 3.20)

project(DungeonCrawler LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)

set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
  raylib
  GIT_REPOSITORY https://github.com/raysan5/raylib.git
  GIT_TAG 5.0
)

FetchContent_MakeAvailable(raylib)

add_executable(DungeonCrawler
  src/main.cpp
  src/Map.cpp
  src/Room.cpp
  src/Player.cpp
  src/Enemy.cpp
)

target_include_directories(DungeonCrawler PRIVATE
  ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(DungeonCrawler PRIVATE raylib)