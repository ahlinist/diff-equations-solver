file(GLOB SOURCES
    tests.cpp 
    */*.cpp
    ../src/*/*.cpp
)

add_executable(${PROJECT_NAME}Tests ${SOURCES})

target_link_libraries(${PROJECT_NAME}Tests gtest gtest_main gmock)
