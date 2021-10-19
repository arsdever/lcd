#pragma once

#ifndef NDEBUG
#	define lcd_assert(condition, message)                                                                             \
		do                                                                                                             \
			{                                                                                                          \
				if (!(condition))                                                                                      \
					{                                                                                                  \
						std::cerr << "Assertion `" #condition "` failed in " << __FILE__ << " line " << __LINE__       \
								  << ": " << message << std::endl;                                                     \
						std::terminate();                                                                              \
					}                                                                                                  \
			}                                                                                                          \
		while (false)
#else
#	define lcd_assert(condition, message)                                                                             \
		do                                                                                                             \
			{                                                                                                          \
			}                                                                                                          \
		while (false)
#endif