#include <chrono>
#include <thread>
#include"TimeManager.h"

namespace GameEngine {
	TimeManager::TimeManager(const std::string &name = "")
	{
		if (name != "") this->m_log_file.open(name);
	}

	TimeManager::~TimeManager()
	{
		this->m_log_file.close();
	}

	void TimeManager::StartTimer(void) {
		this->m_start = std::chrono::system_clock::now();
	}

	double TimeManager::GetCurrentTimer(void) {
		auto now = std::chrono::system_clock::now();
		std::chrono::duration<double> end = now - this->m_start;
		return (end.count() * 1000);
	}

	double TimeManager::GetLastTime(void) {
		return (m_last_time);
	}

	void TimeManager::WaitFPS(unsigned short fps_number) {
		static double frame_milliseconds = 1000 / fps_number;
		double current = this->GetCurrentTimer();
		int to_sleep = (int)(frame_milliseconds - current) * 1000;
		std::this_thread::sleep_for(std::chrono::microseconds(to_sleep));
		this->m_last_time = this->GetCurrentTimer();
		if (this->m_log_file.is_open()) this->m_log_file << "Time save at " << this->GetCurrentTimer() << "ms" << std::endl;
	}
}
