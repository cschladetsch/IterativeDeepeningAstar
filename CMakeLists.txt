cmake_minimum_required(VERSION 3.29)
project(DefaultSDL2 VERSION 1.0 DESCRIPTION "Project with Boost and SDL2")

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

# Define the executable
add_executable(${PROJECT_NAME} main.cpp)

# Link with SDL2 and Boost libraries
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${Boost_LIBRARIES})

