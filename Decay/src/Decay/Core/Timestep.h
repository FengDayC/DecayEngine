#pragma once

namespace Decay
{
	class Timestep
	{
	public:
		Timestep(float time = .0f) : m_Time(time)
		{

		}

		inline void SetSeconds(float time) { m_Time = time; }

		inline float GetSeconds() const { return m_Time; }
		inline float GetMilliSeconds() const { return m_Time * 1000.0f; }

		inline operator float() { return m_Time; }

		inline Timestep operator +(const Timestep& b)
		{
			return Timestep(m_Time + b.m_Time);
		}

		inline Timestep operator -(const Timestep& b)
		{
			return Timestep(m_Time - b.m_Time);
		}

		inline Timestep operator +(const float& b)
		{
			return Timestep(m_Time + b);
		}

		inline Timestep operator -(const float& b)
		{
			return Timestep(m_Time - b);
		}

	private:
		float m_Time;
	};
}
