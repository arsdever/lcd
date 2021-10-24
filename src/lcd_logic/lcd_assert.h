#pragma once

#include <logger.h>

#ifndef NDEBUG
#	define lcd_assert(condition, message)                                                                             \
		do                                                                                                             \
			{                                                                                                          \
				if (!(condition))                                                                                      \
					{                                                                                                  \
						logger::critical(std::string("Assertion `" #condition "` failed in ") +                        \
										 std::string(__FILE__) + std::string(" line ") + std::to_string(__LINE__) +    \
										 std::string(": ") + std::string(message) + std::string("\n"));                \
						std::terminate();                                                                              \
					}                                                                                                  \
			}                                                                                                          \
		while (false)
#else
#	define lcd_assert(contition, message)                                                                             \
		do                                                                                                             \
			{                                                                                                          \
			}                                                                                                          \
		while (false)
#endif