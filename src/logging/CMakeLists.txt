cmake_minimum_required (VERSION 3.16)

add_library (logging STATIC "logger.h" "stdafx.h" "logging_prototypes.h")

if (NOT ${spdlog_FOUND})
	target_sources (logging PRIVATE "logger.cpp")
else()
	target_sources (logging PRIVATE "adapter/spdlog/spdlog_helper.h" "adapter/spdlog/spdlog_helper.cpp""adapter/spdlog/spdlog_logger.cpp")
endif()

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
