#pragma once

namespace Decay
{
	enum class ImageFormat
	{
		R,
		RGB,
		RGBA,
		UNKOWN
	};

	class DECAY_API Texture
	{
	public:
		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		virtual void Bind(uint32_t slot = 0) const = 0;
		virtual void SetData(void* data, uint32_t size) = 0;

		virtual bool operator==(const Texture& other) const = 0;
	};

	class DECAY_API Texture2D : public Texture
	{
	public:
		static S_PTR<Texture2D> Create(uint32_t width, uint32_t height);
		static S_PTR<Texture2D> Create(const std::string path);
		static S_PTR<Texture2D> Create(ImageFormat colorFormat, uint32_t width, uint32_t height, void* data);

	public:
		static S_PTR<Texture> GetWhite();
	};
}
