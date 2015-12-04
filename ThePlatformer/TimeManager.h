#pragma once

#include <fstream>
#include <chrono>

namespace GameEngine {
	class TimeManager
	{
	public:
		TimeManager(const std::string& = "");
		void	StartTimer(void);
		double	GetCurrentTimer(void);
		double  GetLastTime(void);
		void	WaitFPS(unsigned short);
		~TimeManager();
	private:
		double												m_last_time;
		std::ofstream										m_log_file;
		std::chrono::time_point<std::chrono::system_clock>	m_start;
	};
}