cmake_minimum_required(VERSION 2.8)
project(myprojct CXX)
add_compile_options(-std=c++14)

find_package(PCL 1.8 REQUIRED)
include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

include_directories(include)

add_executable(main src/main.cpp)
target_link_libraries (main ${PCL_LIBRARIES})
