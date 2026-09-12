cmake_minimum_required(VERSION 3.10)
project(Lab1 VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(lab1lib STATIC
    src/rect.cpp
    src/mystring.cpp
    src/barrel.cpp
    src/text_wrapper.cpp
    src/matrix.cpp
)

target_include_directories(lab1lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_compile_options(lab1lib PRIVATE -Wall -Wextra)

add_executable(lab1 src/lab1.cpp)
target_link_libraries(lab1 PRIVATE lab1lib)
enable_testing()
add_subdirectory(tests)