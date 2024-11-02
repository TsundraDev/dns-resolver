cmake_minimum_required(VERSION 3.28)
set(CMAKE_CXX_STANDARD 20)

project(dns-resolver)

# Create test executable
add_executable(dns-resolver
  src/main.cpp
)

include_directories(src)
