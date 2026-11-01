cmake_minimum_required(VERSION 3.20)
project(ledmatrix-cpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(ledmatrix-cpp src/ledmatrix.cpp)
target_include_directories(ledmatrix-cpp PUBLIC include)

add_executable(ledmatrix-cpp-test examples/main.cpp)
target_link_libraries(ledmatrix-cpp-test PRIVATE ledmatrix-cpp)

target_compile_options(ledmatrix-cpp PRIVATE -Wall -Wextra -Wpedantic)
target_compile_options(ledmatrix-cpp-test PRIVATE -Wall -Wextra -Wpedantic)
