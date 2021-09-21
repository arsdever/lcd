cmake_minimum_required (VERSION 3.8)

add_library (lcd_logic STATIC "lcd_controller.h" "lcd_controller.cpp" "port.h" "display.h" "display.cpp" "i_character_data.h" "scheduler.h" "scheduler.cpp")

add_executable (lcd_logic_test "test.cpp" "scheduler.h" "scheduler.cpp")
target_include_directories (lcd_logic PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(lcd_logic_test PUBLIC lcd_logic)

target_precompile_headers (lcd_logic PUBLIC stdafx.h)
target_precompile_headers (lcd_logic_test REUSE_FROM lcd_logic)
