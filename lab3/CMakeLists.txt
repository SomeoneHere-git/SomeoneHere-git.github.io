cmake_minimum_required(VERSION 3.14)
project(Lab3_UnitTests CXX)

set(CMAKE_CXX_STANDARD 17)

# --- Google Test (системний пакет або FetchContent) ---
find_package(GTest QUIET)
if(NOT GTest_FOUND)
    include(FetchContent)
    FetchContent_Declare(googletest
        SOURCE_DIR /usr/src/googletest)
    FetchContent_MakeAvailable(googletest)
else()
    include(GoogleTest)
endif()

# --- Бібліотека модуля ---
add_library(lab3_lib
    src/task.cpp
    src/team.cpp
)
target_include_directories(lab3_lib PUBLIC src)

# --- Виконуваний файл тестів ---
add_executable(lab3_tests
    tests/test_main.cpp
)
target_link_libraries(lab3_tests
    lab3_lib
    GTest::gtest_main
)

# --- Підключення CTest ---
enable_testing()
include(GoogleTest)
gtest_discover_tests(lab3_tests)

# --- Покриття (lcov/gcov, тільки на GCC/Clang) ---
option(ENABLE_COVERAGE "Enable code coverage" OFF)
if(ENABLE_COVERAGE)
    target_compile_options(lab3_lib     PRIVATE --coverage -O0 -g)
    target_link_options   (lab3_lib     PRIVATE --coverage)
    target_compile_options(lab3_tests   PRIVATE --coverage -O0 -g)
    target_link_options   (lab3_tests   PRIVATE --coverage)
endif()
