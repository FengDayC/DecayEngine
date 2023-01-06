#pragma once
#include <memory>
#include"Application.h"

extern std::shared_ptr<Decay::Application> Decay::CreateApplication();

int main(int argc, char** argv)
{
	auto application = Decay::CreateApplication();
	application->Run();
}