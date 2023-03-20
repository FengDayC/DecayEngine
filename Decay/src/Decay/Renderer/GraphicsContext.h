#pragma once
namespace Decay
{
	class DECAY_API GraphicsContext
	{
	public :
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
	};
}