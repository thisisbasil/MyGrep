# MyGrep
# barebones grep implementation of grep in c++20
# Basil Huffman (bahuffma@gmail.com)

cmake_minimum_required(VERSION 3.0...3.31)

project(MyGrep)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "-Wall -pthread")

if (LINUX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lstdc++fs")
endif()

add_executable(MyGrep src/main.cpp)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()
add_executable(MyGrepTest src/test.cpp)
target_link_libraries(
  MyGrepTest
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(MyGrepTest)
