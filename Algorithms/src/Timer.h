#pragma once

#include <chrono>
#include <iostream>

namespace HUtil
{
	class Timer
	{
	public:
		Timer()
		{
			m_StartTimePoint = std::chrono::high_resolution_clock::now();
		}

		~Timer()
		{
			auto endTimePoint = std::chrono::high_resolution_clock::now();
			
			auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimePoint).time_since_epoch().count();
			auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimePoint).time_since_epoch().count();
			
			auto duration_Micro = end - start;
			double duration_Milli = duration_Micro * 0.001;

			std::cout << "Duration: " << duration_Milli << "ms" << std::endl;
		}

	private:
		std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimePoint;

	};
}
