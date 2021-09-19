cmake_minimum_required (VERSION 3.8)

add_library (lcd_gui_qt STATIC "mainscreen.h" "mainscreen.cpp" "lcd_widget.h" "lcd_widget.cpp")

target_include_directories (lcd_gui_qt PUBLIC ${CMAKE_SOURCE_DIR}/src/lcd_logic)
target_link_libraries (lcd_gui_qt PUBLIC Qt5::Core Qt5::Gui Qt5::Widgets lcd_logic)
# target_precompile_headers (lcd_gui REUSE_FROM lcd_logic)
