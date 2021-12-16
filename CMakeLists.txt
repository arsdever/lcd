# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

option (BUILD_TESTS OFF)

project ("lcd")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)

option (COVERAGE_REPORT "Enable coverage reporting" OFF)
if (COVERAGE_REPORT AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
  # Add required flags (GCC & LLVM/Clang)
  add_compile_options (
    -O0        # no optimization
    -g         # generate debug info
    --coverage # sets all required flags
  )
  add_link_options (--coverage)
endif ()

if (${BUILD_TESTS})
	message ("Tests enabled")
	enable_testing ()
	add_subdirectory (test)
endif ()

# Include sub-projects.
add_subdirectory ("src")
