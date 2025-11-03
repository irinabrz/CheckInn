cmake_minimum_required(VERSION 3.25)
project(CheckInn)

set(CMAKE_CXX_STANDARD 17)

add_executable(CheckInn main.cpp)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/artifacts/bin")


