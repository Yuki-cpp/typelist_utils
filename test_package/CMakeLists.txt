cmake_minimum_required(VERSION 3.22)
project(PackageTest CXX)

message(${CMAKE_VERSION})

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 20)

find_package(typelist_utils CONFIG REQUIRED)

add_executable(example src/example.cpp)
target_link_libraries(example typelist_utils::typelist_utils)
