# This project requires CMake v3.20 or higher.
cmake_minimum_required(VERSION 3.20)

# It is C++ project.
project(FishCode CXX)

# It is FishCode (fishcode) v1.1.
set(CMAKE_PROJECT_VERSION_MAJOR 1)
set(CMAKE_PROJECT_VERSION_MINOR 1)

# The project requires C++20 standard.
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# This project doesn't use any platform-specific extensions.
set(CMAKE_CXX_EXTENSIONS OFF)

# The main executable and its dependecies.
add_executable(fishcode
  "sources/block.cpp"
  "sources/block.hpp"
  "sources/commands.hpp"
  "sources/error.cpp"
  "sources/error.hpp"
  "sources/file.cpp"
  "sources/file.hpp"
  "sources/fishcode.cpp"
  "sources/fishcode.hpp"
  "sources/key.cpp"
  "sources/key.hpp"
  "sources/main.cpp"
  "sources/manual.hpp"
  "sources/messages.hpp"
  "sources/password.cpp"
  "sources/password.hpp"
  "sources/string.hpp"
)

