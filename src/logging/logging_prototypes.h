#pragma once

#define POINTERIZE(classname)                                                                                          \
	class classname;                                                                                                   \
	using classname##_ptr  = std::shared_ptr<classname>;                                                               \
	using classname##_wptr = std::weak_ptr<classname>;                                                                 \
	using classname##_uptr = std::unique_ptr<classname>;

namespace lcd
{
	POINTERIZE(logger)
	POINTERIZE(log_history)
	POINTERIZE(log_history_sink)
} // namespace lcd
