# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "src\\app\\CMakeFiles\\app_autogen.dir\\AutogenUsed.txt"
  "src\\app\\CMakeFiles\\app_autogen.dir\\ParseCache.txt"
  "src\\app\\app_autogen"
  "src\\lcd_gui_qt\\CMakeFiles\\lcd_gui_qt_autogen.dir\\AutogenUsed.txt"
  "src\\lcd_gui_qt\\CMakeFiles\\lcd_gui_qt_autogen.dir\\ParseCache.txt"
  "src\\lcd_gui_qt\\lcd_gui_qt_autogen"
  "src\\lcd_logic\\CMakeFiles\\lcd_logic_autogen.dir\\AutogenUsed.txt"
  "src\\lcd_logic\\CMakeFiles\\lcd_logic_autogen.dir\\ParseCache.txt"
  "src\\lcd_logic\\CMakeFiles\\lcd_logic_test_autogen.dir\\AutogenUsed.txt"
  "src\\lcd_logic\\CMakeFiles\\lcd_logic_test_autogen.dir\\ParseCache.txt"
  "src\\lcd_logic\\lcd_logic_autogen"
  "src\\lcd_logic\\lcd_logic_test_autogen"
  )
endif()
