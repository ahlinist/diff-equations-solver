cmake_minimum_required(VERSION 3.22.1)

project(DifferentialEquationsSolverTests)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SOURCES
    tests.cpp 
    */*.cpp
    ../src/*/*.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} gtest gtest_main gmock)

enable_testing() #TODO: make it work with "make test"

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})
