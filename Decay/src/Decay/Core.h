#pragma once

#include <memory>
#include <utility>

#ifdef DECAY_PLATFORM_WINDOWS
	
#ifdef DECAY_DYNAMIC_LINK
	#ifdef DECAY_BUILD_DLL
		#define DECAY_API _declspec(dllexport)
	#else
		#define DECAY_API _declspec(dllimport)
	#endif
#else
	#define DECAY_API
#endif

#else
#error Only support windows!
#endif

#ifdef DECAY_ENABLE_ASSERTS
#define DC_ASSERT(x,...) {if(!(x)){ DC_ERROR("Assersion Failed:{0}",__VA_ARGS__); __debugbreak();}}
#define DC_CORE_ASSERT(x,...) {if(!(x)){ DC_CORE_ERROR("Assersion Failed:{0}",__VA_ARGS__); __debugbreak();}}
#else
#define DC_ASSERT(x,...)
#define DC_CORE_ASSERT(x,...)
#endif

#define BIT(x) (1<<(x))
#define LOWBIT(x) ((x)&(-(x)))

#define DC_BIND_EVENT(Fn) std::bind(&Fn,this,std::placeholders::_1)

//----std----
template<typename x>
using S_PTR = std::shared_ptr<x>;
template<typename T,typename... Args>
constexpr S_PTR<T> CreateS_PTR(Args&&... args)
{
	return std::make_shared<T>(std::forward<Args>(args)...);
}

template<typename x>
using U_PTR = std::unique_ptr<x>;
template<typename T,typename... Args>
constexpr U_PTR<T> CreateU_PTR(Args&&... args)
{
	return std::make_unique<T>(std::forward<Args>(args)...);
}

template<typename x>
using W_PTR = std::weak_ptr<x>;
template<typename T,typename... Args>
constexpr W_PTR<T> CreateW_PTR(Args&&... args)
{
	return std::make_weak<T>(std::forward<Args>(args)...);
}

template<typename x,typename y>
using PAIR = std::pair<x,y>;
template<typename x,typename y>
constexpr PAIR<x,y> CreatePAIR(x&& x_,y&& y_)
{
	return std::make_pair(std::forward<x>(x_),std::forward<y>(y_));
}
