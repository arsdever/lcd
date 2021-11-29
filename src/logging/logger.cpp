#include <stdafx.h>

#include <iostream>
#include <logger.h>

#define SET_LOG_LEVEL(lvl)			((void)lvl)
#define LOG_METHOD(method, message) std::cout << #method << ": " << message << std::endl;

namespace lcd
{
	void logger::set_log_level(log_level const& level) { SET_LOG_LEVEL(level); }
	void logger::info(std::string const& message) { LOG_METHOD(info, message); }
	void logger::warn(std::string const& message) { LOG_METHOD(warn, message); }
	void logger::error(std::string const& message) { LOG_METHOD(error, message); }
	void logger::critical(std::string const& message) { LOG_METHOD(critical, message); }
	void logger::debug(std::string const& message) { LOG_METHOD(debug, message); }
} // namespace lcd
