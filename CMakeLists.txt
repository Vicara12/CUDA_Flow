cmake_minimum_required(VERSION 3.10)

project(CUDA_Flow VERSION 1.0 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    src/main.cpp
    src/solver/solver.cpp
)

add_executable(cuda_flow ${SOURCES})
target_include_directories(cuda_flow PUBLIC include)