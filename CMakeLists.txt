cmake_minimum_required(VERSION 3.10)
project(RayTracer)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 20)

# Include directories
include_directories(include)

# Add your source files
file(GLOB SOURCES "src/*.cpp")

# Create executable
add_executable(main ${SOURCES})

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
