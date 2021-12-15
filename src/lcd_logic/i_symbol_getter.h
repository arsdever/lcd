#pragma once

namespace lcd
{
	class i_symbol_getter
	{
	public:
		virtual ~i_symbol_getter() = default;

		virtual std::array<char, 8> get_symbol_ddram(size_t row, size_t column) const = 0;
	};
} // namespace lcd
