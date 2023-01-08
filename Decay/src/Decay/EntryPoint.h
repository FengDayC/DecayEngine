#pragma once
#include "Application.h"
#include "Log.h"

#ifdef  DECAY_PLATFORM_WINDOWS


extern S_PTR(Decay::Application) Decay::CreateApplication();

int main(int argc, char** argv)
{
	Decay::Log::Init();
	DC_WARN("Client Logger Inited!");
	DC_CORE_WARN("Core Logger Inited!");

	auto application = Decay::CreateApplication();
	application->Run();
}

#endif //  DECAY_PLATFORM_WINDOWS