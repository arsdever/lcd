find_package (Qt5Core QUIET)
find_package (Qt5Gui QUIET)
find_package (Qt5Widgets QUIET)
find_package (spdlog QUIET)

if (NOT ${Qt5Gui_FOUND} OR NOT ${Qt5Core_FOUND} OR NOT ${Qt5Widgets_FOUND})
	message ("QT5 not found. Disabling QT gui project")
else ()
	add_subdirectory (app)
	add_subdirectory (lcd_gui_qt)
endif ()

if (NOT ${spdlog_FOUND})
	message ("spdlog not found. Falling back to std logging")
	add_compile_definitions(NO_SPDLOG)
endif()

add_subdirectory (logging)
add_subdirectory (lcd_logic)
