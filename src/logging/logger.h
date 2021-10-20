#pragma once

namespace lcd
{
	class logger
	{
	public:
		static void info(std::string const& message);
		static void warn(std::string const& message);
		static void error(std::string const& message);
		static void critical(std::string const& message);
		static void debug(std::string const& message);
	};
} // namespace lcd
