#pragma once

namespace Decay
{
	template<typename Fn>
	class DECAY_API Timer
	{
	public:
		Timer(const std::string& name, Fn&& callbackFunc = nullptr);
		~Timer();

	private:
		void Stop();

	private:
		std::string m_Name;
		std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimePoint;
		bool m_Stopped;
		Fn m_Callback;
	};
}