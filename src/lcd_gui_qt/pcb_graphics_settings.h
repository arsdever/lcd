#pragma once

namespace lcd
{
	struct pcb_graphics_settings
	{
		QColor dark_color;
		QColor light_color;
		QColor gold_color;
		QColor solder_color;
		QColor display_light_color;
		QColor display_dark_color;
		QColor display_pixel_color;
		QColor display_pixel_enabled_color;
		float  through_hole_radius;
		float  through_hole_width;
		float  trace_width;
		float  clearance;
	};

	extern pcb_graphics_settings g_pcb_graphics_settings;
} // namespace lcd