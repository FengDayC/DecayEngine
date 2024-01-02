#pragma once
#include"Core.h"
#include"spdlog\spdlog.h"
#include"spdlog\fmt\ostr.h"

namespace Decay
{
	class DECAY_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }

		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;

		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

//Log Macros
#define DC_CORE_TRACE(...) Decay::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define DC_CORE_INFO(...)  Decay::Log::GetCoreLogger()->info(__VA_ARGS__)
#define DC_CORE_WARN(...)  Decay::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define DC_CORE_ERROR(...) Decay::Log::GetCoreLogger()->error(__VA_ARGS__)

#define DC_TRACE(...)	   Decay::Log::GetClientLogger()->trace(__VA_ARGS__)
#define DC_INFO(...)	   Decay::Log::GetClientLogger()->info(__VA_ARGS__)
#define DC_WARN(...)	   Decay::Log::GetClientLogger()->warn(__VA_ARGS__)
#define DC_ERROR(...)	   Decay::Log::GetClientLogger()->error(__VA_ARGS__)