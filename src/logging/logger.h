#pragma once

namespace lcd
{
	class logger
	{
	public:
		enum class log_level
		{
			info,
			debug,
			warn,
			error,
			critical
		};

	public:
		static void set_log_level(log_level const& level);
		static void info(std::string const& message);
		static void warn(std::string const& message);
		static void error(std::string const& message);
		static void critical(std::string const& message);
		static void debug(std::string const& message);
	};
} // namespace lcd
