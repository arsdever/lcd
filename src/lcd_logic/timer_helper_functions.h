#pragma once

namespace lcd
{
	// https://stackoverflow.com/a/16606128/10185183
	template <typename T>
	std::string to_string_with_precision(const T a_value, const int n = 6)
	{
		std::ostringstream out;
		out.precision(n);
		out << std::fixed << a_value;
		return out.str();
	}

	std::string time_string(double time, int precision = 6)
	{
		std::string suffix;
		if (time < .000000001)
			{
				time *= 1000000000000.0f;
				suffix = "ps";
			}
		else if (time < .000001)
			{
				time *= 1000000000.0f;
				suffix = "ns";
			}
		else if (time < .001)
			{
				time *= 1000000.0f;
				suffix = "us";
			}
		else if (time < 1)
			{
				time *= 1000.0f;
				suffix = "ms";
			}
		else if (time < 60)
			{
				suffix = "s";
			}
		else if (time < 60)
			{
				time /= 60;
				suffix = "m";
			}
		else
			{
				time /= 3600;
				suffix = "h";
			}

		return to_string_with_precision(time, precision) + suffix;
	}
} // namespace lcd