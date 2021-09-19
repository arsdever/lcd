# CMakeList.txt : CMake project for carui, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (app "application.cpp")

target_include_directories (app PUBLIC
${CMAKE_SOURCE_DIR}/src/lcd_logic
${CMAKE_SOURCE_DIR}/src/lcd_gui_qt)
target_link_libraries (app PUBLIC lcd_gui_qt)
target_precompile_headers (app PUBLIC stdafx.h)

# TODO: Add tests and install targets if needed.
