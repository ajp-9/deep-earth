#pragma once

#include <chrono>

namespace engine
{
	class Timer
	{
	public:

		Timer(const char* name = "Anonymous", bool print_us = false);

		~Timer();

		void stop();

	private:

		const char* m_Name;
		std::chrono::time_point<std::chrono::high_resolution_clock> m_startTimepoint;
		bool m_Print_US;
		bool m_Stopped;
	};
}
