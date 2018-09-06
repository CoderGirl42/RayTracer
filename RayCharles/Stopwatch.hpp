#pragma once

#include <type_traits>
#include <chrono>


class Stopwatch final
{
public:

	using elapsed_resolution = std::chrono::milliseconds;

	Stopwatch()
	{
		reset();
	}

	void reset()
	{
		reset_time = clock.now();
	}

	elapsed_resolution elapsed()
	{
		return std::chrono::duration_cast<elapsed_resolution>(clock.now() - reset_time);
	}

private:

	std::chrono::high_resolution_clock clock;
	std::chrono::high_resolution_clock::time_point reset_time;
};