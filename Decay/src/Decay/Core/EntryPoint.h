#pragma once
#include "Application.h"
#include "Decay\Log\Log.h"
#include "Decay\Profile\Instrumentor.hpp"

#ifdef  DECAY_PLATFORM_WINDOWS


extern void Decay::CreateApplication();

int main(int argc, char** argv)
{
	Decay::Log::Init();

	DC_PROFILE_BEGIN_SESSION("Startup", "Decay-Profile-Startup.json");
	Decay::CreateApplication();
	DC_PROFILE_END_SESSION();
	DC_PROFILE_BEGIN_SESSION("Runtime", "Decay-Profile-Runtime.json");
	Decay::Application::GetApplication().Run();
	DC_PROFILE_END_SESSION();
	DC_PROFILE_BEGIN_SESSION("Shutdown", "Decay-Profile-Shutdown.json");
	Decay::Application::ReleaseApplication();
	DC_PROFILE_END_SESSION();
}

#endif //  DECAY_PLATFORM_WINDOWS