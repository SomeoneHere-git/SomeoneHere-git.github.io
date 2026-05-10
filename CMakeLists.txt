set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
cmake_minimum_required(VERSION 3.15)
project(TaskManagerProject LANGUAGES CXX)

# 1. Знаходимо залежності (Conan має створити ці конфіги)
find_package(stduuid REQUIRED)
find_package(Catch2 REQUIRED)

# 2. Збираємо основну логіку як бібліотеку (module1)
message(STATUS "stduuid include dirs: ${stduuid_INCLUDE_DIRS}")
file(GLOB MODULE1_SOURCES "./src/TaskManagement/*.cpp")

# Видаляємо тести зі списку вихідних файлів бібліотеки
#
list(FILTER MODULE1_SOURCES EXCLUDE REGEX ".*_test\\.cpp$") 

add_library(module1 ${MODULE1_SOURCES})

# Важливо: додаємо шлях до хедерів, щоб TaskApp міг їх знайти
target_include_directories(module1 PUBLIC "./src/TaskManagement")

# Лінкуємо uuid до бібліотеки, де він використовується
target_link_libraries(module1 PUBLIC stduuid::stduuid)

# 3. Основний додаток
# В add_executable краще додавати лише файл з функцією main()
add_executable(TaskApp ./src/main.cpp) 
target_link_libraries(TaskApp PRIVATE module1)

# 4. Тести
if(BUILD_TESTING)
    # Шукаємо всі файли тестів у папці
    file(GLOB TEST_SOURCES "./src/TaskManagement/*_test.cpp")
    
    add_executable(unit_tests ${TEST_SOURCES})
    # Тести залежать від нашої бібліотеки та Catch2
    target_link_libraries(unit_tests PRIVATE module1 Catch2::Catch2WithMain)
endif()
