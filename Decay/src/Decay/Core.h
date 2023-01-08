#pragma once

#ifdef DECAY_PLATFORM_WINDOWS
	#ifdef DECAY_BUILD_DLL
		#define DECAY_API _declspec(dllexport)
	#else
		#define DECAY_API _declspec(dllimport)
	#endif
#else
#error Only support windows!
#endif

#define BIT(x) (1<<x)