cmake_minimum_required(VERSION 3.20)
project(CheckInn LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set output directory for binaries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Include headers
include_directories(${CMAKE_SOURCE_DIR}/include)

# Source files
set(SOURCES
        src/main.cpp
        src/Client.cpp
        src/Room.cpp
        src/Booking.cpp
        src/Hotel.cpp
)

# Create executable
add_executable(CheckInn ${SOURCES})


