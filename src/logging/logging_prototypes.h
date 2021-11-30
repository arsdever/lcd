#pragma once

#define POINTERIZE_I(classname)                                                                                        \
	class i_##classname;                                                                                                 \
	using classname##_ptr  = std::shared_ptr<i_##classname>;                                                           \
	using classname##_wptr = std::weak_ptr<i_##classname>;                                                             \
	using classname##_uptr = std::unique_ptr<i_##classname>;

#define POINTERIZE(classname)                                                                                          \
	class classname;                                                                                                   \
	using classname##_ptr  = std::shared_ptr<classname>;                                                               \
	using classname##_wptr = std::weak_ptr<classname>;                                                                 \
	using classname##_uptr = std::unique_ptr<classname>;

namespace lcd
{
	POINTERIZE(logger)
	POINTERIZE(log_history_sink)

	POINTERIZE_I(log_history)
} // namespace lcd
