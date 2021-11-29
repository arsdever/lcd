cmake_minimum_required (VERSION 3.16)

add_library (logging STATIC "logger.h" "stdafx.h" "logging_prototypes.h" "log_history.h" "log_history.cpp" "factory/log_history_sink_factory.h" "log_history_sink.h" "log_history_sink.cpp")

if (NOT ${spdlog_FOUND})
	target_sources (logging PRIVATE "logger.cpp")
else()
	target_sources (logging PRIVATE "adapter/spdlog/spdlog_helper.h" "adapter/spdlog/spdlog_helper.cpp" "adapter/spdlog/spdlog_logger.cpp" "adapter/spdlog/spdlog_history_sink.h" "adapter/spdlog/spdlog_history_sink_factory.cpp" "adapter/spdlog/spdlog_history_sink.cpp")
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
