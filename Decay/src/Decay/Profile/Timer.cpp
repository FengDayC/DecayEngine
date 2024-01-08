#include "dcpch.h"
#include "Timer.h"

namespace Decay
{
	template<typename Fn>
	Timer<Fn>::Timer(const std::string& name, Fn&& callbackFunc)
		: m_Name(name), m_Callback(callbackFunc), m_Stopped(false)
	{
		m_StartTimePoint = std::chrono::high_resolution_clock::now();
	}

	template<typename Fn>
	Timer<Fn>::~Timer()
	{
		if (!m_Stopped)
		{
			m_Stopped = true;
			Stop();
		}
	}

	template<typename Fn>
	void Timer<Fn>::Stop()
	{
		auto endTimePoint = std::chrono::high_resolution_clock::now();

		long long start = std::chrono::time_point_cast<std::chrono::milliseconds>(m_StartTimePoint).time_since_epoch().count();
		long long end = std::chrono::time_point_cast<std::chrono::milliseconds>(endTimePoint).time_since_epoch().count();
	
		float duration = (end - start) * 0.001f;

		DC_CORE_INFO("Profile: %.2f ms %s", duration, m_Name.c_str())

		if (m_Callback != nullptr)
		{
			m_Callback({ m_Name,duration });
		}
	}
}


