cmake_minimum_required (VERSION 3.8)

add_library (lcd_logic STATIC "lcd_controller.h" "lcd_controller.cpp" "port.h" "display.h" "display.cpp" "i_symbol_getter.h" "scheduler.h" "scheduler.cpp" "i_timer.h" "realtime_timer.h" "realtime_timer.cpp" "lcd_assert.h" "timer_helper_functions.h" "pin.h" "pin.cpp" "event.h" "event_connection.h" "uuid.h" "data_bulk.h" "step_timer.h" "step_timer.cpp" "logging/logger_with_timing.h" "logging/logger_with_timing.cpp" "lcd_logic_prototypes.h")

target_include_directories (lcd_logic
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/../logging/
)

target_precompile_headers (lcd_logic PUBLIC stdafx.h)
