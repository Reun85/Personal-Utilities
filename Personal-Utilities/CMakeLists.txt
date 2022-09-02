# CMakeList.txt : CMake project for Personal-Utilities, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

file(GLOB_RECURSE SOURCE_FILES "*.cpp")

# Add source to this project's executable.
add_executable (Personal-Utilities "Personal-Utilities.cpp" SOURCE_FILES)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Personal-Utilities PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
