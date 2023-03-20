#pragma once
#include"Decay\Core\Events\Event.h"

namespace Decay
{
	/// <summary>
	/// 窗口创建参数
	/// </summary>
	struct WindowProps
	{
		std::string Title;
		uint32_t Width;
		uint32_t Height;

		WindowProps(const std::string& title = "Decay Engine",
			uint32_t width = 1280,
			uint32_t height = 720):Title(title),Width(width),Height(height)
		{}
	};

	/// <summary>
	/// 窗口抽象类（具体由平台实现）
	/// </summary>
	class DECAY_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() = default;

		virtual void OnUpdate() = 0;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void* GetNativeWindow() const = 0;
 
		static Window* Create(const WindowProps& props = WindowProps());
	};
}