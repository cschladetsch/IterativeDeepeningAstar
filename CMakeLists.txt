cmake_minimum_required(VERSION 3.29)
set(PROJECT_NAME Astar)
set(LIBRARY_NAME AstarLibrary)

project(${PROJECT_NAME} VERSION 1.0 DESCRIPTION "Iterative Deepening Astar")

# Use C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# SDL2
set(SDL2_ROOT_DIR "c:\\SDL2\\SDL2-devel-2.30.2-VC\\SDL2-2.30.2")
set(SDL2_DIR ${SDL2_ROOT_DIR})
find_package(SDL2 REQUIRED HINTS ${SDL2_ROOT_DIR})
include_directories(${SDL2_INCLUDE_DIRS})

# Boost
find_package(Boost 1.84.0 REQUIRED)
find_package(Boost REQUIRED COMPONENTS chrono filesystem system)
include_directories(${Boost_INCLUDE_DIR})

include_directories(include)

# Headers
file(GLOB_RECURSE HEADER_FILES "include/*.hpp")

# Library
file(GLOB_RECURSE LIB_SOURCES "library/*.cpp")
add_library(${LIBRARY_NAME} STATIC ${LIB_SOURCES})

# Executable
file(GLOB_RECURSE APP_SOURCES "source/*.cpp")
add_executable(${PROJECT_NAME} ${HEADER_FILES} ${APP_SOURCES})

# Link with SDL2, Boost libraries, and the custom static library
target_link_libraries(${PROJECT_NAME} ${LIBRARY_NAME} ${SDL2_LIBRARIES} ${Boost_LIBRARIES})

file(GLOB_RECURSE HEADER_FILES "include/*.hpp")
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/include" PREFIX "include" FILES ${HEADER_FILES})

