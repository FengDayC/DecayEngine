#pragma once

#ifdef DECAY_PLATFORM_WINDOWS
	#ifdef DECAY_BUILD_DLL
		#define DECAY_API __declspec(dllexport)
	#else
		#define DECAY_API __declspec(dllimport)
	#endif
#else
#error Only support windows!
#endif