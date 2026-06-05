cmake_minimum_required(VERSION 3.14)
project(Lab3_UnitTests CXX)

set(CMAKE_CXX_STANDARD 17)

# Генерувати compile_commands.json для SonarLint / SonarQube
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# --- Google Test (системний пакет або FetchContent) ---
find_package(GTest QUIET)
if(NOT GTest_FOUND)
    include(FetchContent)
    FetchContent_Declare(googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        v1.14.0
    )
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
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
# Використовуємо add_test замість gtest_discover_tests для обходу проблеми з кирилицею
add_test(NAME lab3_tests COMMAND lab3_tests)

# --- Покриття (lcov/gcov, тільки на GCC/Clang) ---
option(ENABLE_COVERAGE "Enable code coverage" OFF)
if(ENABLE_COVERAGE)
    target_compile_options(lab3_lib     PRIVATE --coverage -O0 -g)
    target_link_options   (lab3_lib     PRIVATE --coverage)
    target_compile_options(lab3_tests   PRIVATE --coverage -O0 -g)
    target_link_options   (lab3_tests   PRIVATE --coverage)
endif()
