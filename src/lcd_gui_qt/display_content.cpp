#include <stdafx.h>

#include "display_content.h"

#include "pcb_graphics_settings.h"

#include <qpainter>
#include <qpaintevent>

namespace lcd
{
	namespace
	{
		QSize margins { 20, 15 };
	}

	display_content_widget::display_content_widget() { setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed); }

	void display_content_widget::set_settings(display_settings const& settings)
	{
		m_settings = settings;

		setMinimumSize(calculateMinimumSize());
		update();
	}

	QSize display_content_widget::calculateMinimumSize()
	{
		double chw =
			(m_settings.pixel_size + m_settings.pixel_spacing) * (m_settings.char_width - 1) + m_settings.pixel_size;
		double chh =
			(m_settings.pixel_size + m_settings.pixel_spacing) * (m_settings.char_height - 1) + m_settings.pixel_size;

		return QSize((chw + m_settings.char_hspacing) * m_settings.columns - m_settings.char_hspacing,
					 (chh + m_settings.char_vspacing) * m_settings.rows - m_settings.char_vspacing) +
			   margins * 2;
	}

#pragma region QWidget

	void display_content_widget::paintEvent(QPaintEvent* e)
	{
		QPainter painter(this);
		painter.setRenderHint(QPainter::Antialiasing);
		painter.fillRect(e->rect(), g_pcb_graphics_settings.display_light_color);
		painter.translate(margins.width(), margins.height());
		float chw =
			(m_settings.pixel_size + m_settings.pixel_spacing) * (m_settings.char_width - 1) + m_settings.pixel_size;
		float chh =
			(m_settings.pixel_size + m_settings.pixel_spacing) * (m_settings.char_height - 1) + m_settings.pixel_size;

		for (size_t chy = 0; chy < m_settings.rows; ++chy)
			{
				painter.save();

				for (size_t chx = 0; chx < m_settings.columns; ++chx)
					{
						painter.save();

						std::array<char, 8> character = m_settings.get_symbol(chy, chx);
						for (char chrow : character)
							{
								painter.save();

								for (int i = m_settings.char_width - 1; i >= 0; --i)
									{
										painter.fillRect(0,
														 0,
														 m_settings.pixel_size,
														 m_settings.pixel_size,
														 (chrow & (1 << i))
															 ? g_pcb_graphics_settings.display_pixel_enabled_color
															 : g_pcb_graphics_settings.display_pixel_color);
										painter.translate(m_settings.pixel_size + m_settings.pixel_spacing, 0);
									}

								painter.restore();
								painter.translate(0, m_settings.pixel_size + m_settings.pixel_spacing);
							}

						painter.restore();
						painter.translate(chw + m_settings.char_hspacing, 0);
					}

				painter.restore();
				painter.translate(0, chh + m_settings.char_vspacing);
			}
	}

#pragma endregion
} // namespace lcd