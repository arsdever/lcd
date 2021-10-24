cmake_minimum_required (VERSION 3.8)

add_library (lcd_logic STATIC "lcd_controller.h" "lcd_controller.cpp" "port.h" "display.h" "display.cpp" "i_character_data.h" "scheduler.h" "scheduler.cpp" "i_timer.h" "std_timer.h" "std_timer.cpp" "lcd_assert.h")

target_include_directories (lcd_logic
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/../logging/
)

target_precompile_headers (lcd_logic PUBLIC stdafx.h)
