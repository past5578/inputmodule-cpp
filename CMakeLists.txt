cmake_minimum_required(VERSION 3.20)
project(inputmodule-cpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(inputmodule-cpp src/ledmatrix.cpp src/inputmodule.cpp)
target_include_directories(inputmodule-cpp PUBLIC include)

add_executable(ledmatrix-test examples/main.cpp)
target_link_libraries(ledmatrix-test PRIVATE inputmodule-cpp)

target_compile_options(inputmodule-cpp PRIVATE -Wall -Wextra -Wpedantic)
target_compile_options(ledmatrix-test PRIVATE -Wall -Wextra -Wpedantic)
