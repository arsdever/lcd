cmake_minimum_required (VERSION 3.8)

add_library (lcd_gui_qt STATIC "qt_display.h" "qt_display.cpp" "app_main_window.h" "app_main_window.cpp" "port_widget.h" "port_widget.cpp" "pin_widget.h" "pin_widget.cpp" "display_content.h" "display_settings.h" "display_content.cpp" "pcb_graphics_settings.h" "decorations/screen_border.h" "decorations/screen_border.cpp" "pin_tooltip.h" "pin_tooltip.cpp")

target_include_directories (lcd_gui_qt PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/src/lcd_logic)
target_link_libraries (lcd_gui_qt PUBLIC Qt5::Core Qt5::Gui Qt5::Widgets lcd_logic logging)
# target_precompile_headers (lcd_gui REUSE_FROM lcd_logic)
