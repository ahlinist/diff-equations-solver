cmake_minimum_required(VERSION 3.22.1)

project(DifferentialEquationsSolver)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE "Release")

add_subdirectory(src)
add_subdirectory(tests)

enable_testing()

add_test(
    NAME ${PROJECT_NAME}Tests 
    COMMAND ${PROJECT_NAME}Tests
)
