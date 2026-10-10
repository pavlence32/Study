cmake_minimum_required(VERSION 3.14)
project(lab3 C CXX)

find_package(Catch2 3 REQUIRED)

add_library(mm STATIC memory.c)
target_include_directories(mm PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_definitions(mm PRIVATE MM_NO_MAIN)

add_executable(tests tests/test.cpp)
target_link_libraries(tests PRIVATE mm Catch2::Catch2WithMain)
