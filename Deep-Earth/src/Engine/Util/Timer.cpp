#include "Timer.hpp"

#include <iostream>

namespace engine
{
	Timer::Timer(const char* name, bool print_us)
		: m_Name(name), m_Print_US(print_us), m_Stopped(false)
	{
		m_startTimepoint = std::chrono::high_resolution_clock::now();
	}

	Timer::~Timer()
	{
		if (!m_Stopped)
			stop();
	}

	void Timer::stop()
	{
		auto endTimepoint = std::chrono::high_resolution_clock::now();
		auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_startTimepoint).time_since_epoch().count();
		auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

		auto us = end - start;
		double ms = us * .001;

		if (!m_Print_US)
			std::cout << m_Name << ": " << ms << " ms\n";
		else
			std::cout << m_Name << ": " << ms << " ms, " << us << " us\n";

		m_Stopped = true;
	}
}
