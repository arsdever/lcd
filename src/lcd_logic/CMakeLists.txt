cmake_minimum_required (VERSION 3.8)

add_library (lcd_logic STATIC "lcd_controller.h" "lcd_controller.cpp" "port.h" "display.h" "display.cpp")

add_executable (lcd_logic_test "test.cpp")
target_link_libraries(lcd_logic_test PUBLIC lcd_logic)

target_precompile_headers (lcd_logic PUBLIC stdafx.h)
target_precompile_headers (lcd_logic_test REUSE_FROM lcd_logic)
