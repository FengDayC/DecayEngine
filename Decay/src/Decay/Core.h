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

#ifdef DECAY_ENABLE_ASSERTS
#define DC_ASSERT(x,...) {if(!x){ DECAY_ERROR("Assersion Failed:{0}",__VA_ARGS__); __debugbreak();}}
#define DC_CORE_ASSERT(x,...) {if(!x){ DECAY_CORE_ERROR("Assersion Failed:{0}",__VA_ARGS__); __debugbreak();}}
#else
#define DC_ASSERT(x,...)
#define DC_CORE_ASSERT(x,...)
#endif

#define BIT(x) (1<<x)
#define S_PTR(x) std::shared_ptr<x>
#define U_PTR(x) std::unique_ptr<x>
#define W_PTR(x) std::weak_ptr<x>