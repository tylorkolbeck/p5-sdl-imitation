cmake_minimum_required(VERSION 3.22)

project(MyProj
  VERSION 0.1.0
  LANGUAGES CXX
)

# --- global defaults ---
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Helpful for tooling (clangd)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Put CMake helper modules here
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(options)
include(warnings)

add_subdirectory(extern/SDL)

# Generate a version header (optional but nice)
configure_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/include/myproj/version.h.in"
  "${CMAKE_CURRENT_BINARY_DIR}/generated/myproj/version.h"
  @ONLY
)

# Add subprojects
add_subdirectory(src)

option(MYPROJ_BUILD_TESTS "Build tests" ON)
if(MYPROJ_BUILD_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()
