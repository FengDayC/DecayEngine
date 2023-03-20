#pragma once

namespace Decay
{
	class DECAY_API Texture
	{
	public:
		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		virtual void Bind(uint32_t slot = 0) const = 0;
	};

	class DECAY_API Texture2D : public Texture
	{
	public:
		static S_PTR<Texture2D> Create(const std::string path);
	};
}
