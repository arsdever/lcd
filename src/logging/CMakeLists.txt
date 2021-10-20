cmake_minimum_required (VERSION 3.8)

add_library (logging STATIC "logger.h" "logger.cpp" "stdafx.h")

target_precompile_headers (logging
	PRIVATE
		stdafx.h
)

target_include_directories (logging
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries (logging
	PRIVATE
		spdlog::spdlog
)
