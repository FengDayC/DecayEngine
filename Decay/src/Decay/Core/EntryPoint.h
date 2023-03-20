#pragma once
#include "Application.h"
#include "Decay\Log\Log.h"

#ifdef  DECAY_PLATFORM_WINDOWS


extern void Decay::CreateApplication();

int main(int argc, char** argv)
{
	Decay::Log::Init();
	DC_WARN("Client Logger Inited!");
	DC_CORE_WARN("Core Logger Inited!");

	Decay::CreateApplication();
	Decay::Application::GetApplication().Run();
	Decay::Application::ReleaseApplication();
}

#endif //  DECAY_PLATFORM_WINDOWS