#pragma once

#define POINTERIZE_I(classname)                                                                                        \
	class i_##classname;                                                                                               \
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
	POINTERIZE(display)
	POINTERIZE(lcd_controller)
	POINTERIZE(pin)
	POINTERIZE(realtime_timer)
	POINTERIZE(scheduler)
	POINTERIZE(step_timer)

	POINTERIZE_I(symbol_getter)
	POINTERIZE_I(timer)
} // namespace lcd
