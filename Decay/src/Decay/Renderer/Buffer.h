#pragma once
#include "Decay\Core.h"

namespace Decay
{
	enum class ShaderDataType
	{
		None,Float,Float2,Float3,Float4,Int,Int2,Int3,Int4,Mat2,Mat3,Mat4,Bool,Bool2,Bool3,Bool4
	};

	static uint32_t ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Bool:
			return 1;
		case ShaderDataType::Bool2:
			return 2;
		case ShaderDataType::Bool3:
			return 3;
		case ShaderDataType::Float:
		case ShaderDataType::Int:
		case ShaderDataType::Bool4:
			return 4;
		case ShaderDataType::Float2:
		case ShaderDataType::Int2:
			return 8;
		case ShaderDataType::Int3:
		case ShaderDataType::Float3:
			return 12;
		case ShaderDataType::Int4:
		case ShaderDataType::Float4:
		case ShaderDataType::Mat2:
			return 16;
		case ShaderDataType::Mat3:
			return 36;
		case ShaderDataType::Mat4:
			return 64;
		}

		DC_CORE_ASSERT(false, "Unkown shader type");

		return 0;
	}

	struct BufferElement
	{
		std::string Name;
		uint32_t Size;
		uint32_t Offset;
		ShaderDataType Type;
		bool Normalized;

		BufferElement() {}

		BufferElement(ShaderDataType type, const std::string name, bool normalized = false) 
			:Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized)
		{

		}

		uint32_t GetComponentCount() const
		{
			switch (Type)
			{
			case ShaderDataType::Bool:
			case ShaderDataType::Float:
			case ShaderDataType::Int:
				return 1;
			case ShaderDataType::Bool2:
			case ShaderDataType::Float2:
			case ShaderDataType::Int2:
				return 2;
			case ShaderDataType::Bool3:
			case ShaderDataType::Float3:
			case ShaderDataType::Int3:
				return 3;
			case ShaderDataType::Bool4:
			case ShaderDataType::Float4:
			case ShaderDataType::Int4:
			case ShaderDataType::Mat2:
				return 4;
			case ShaderDataType::Mat3:
				return 3*3;
			case ShaderDataType::Mat4:
				return 4*4;
			}

			DC_CORE_ASSERT(false, "Unkown shader type");

			return 0;
		}
	};

	class BufferLayout
	{
	public:

		BufferLayout() {}

		BufferLayout(const std::initializer_list<BufferElement>& elements) : m_Elements(elements) 
		{
			CalOffsetAndStride();
		}

		inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }

		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }

		inline uint32_t GetStride() const { return m_Stride; }

	private:
		void CalOffsetAndStride()
		{
			uint32_t offset = 0;
			m_Stride = 0;
			for (auto& element : m_Elements)
			{
				element.Offset = offset;
				offset += element.Size;
				m_Stride += element.Size;
			}
		}
	private:
		std::vector<BufferElement> m_Elements;
		uint32_t m_Stride;
	};

	class VertexBuffer
	{
	public :
		virtual ~VertexBuffer() {}

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual void SetLayout(const BufferLayout& layout) = 0;
		virtual const BufferLayout& GetLayout() const = 0;

		static VertexBuffer* Create(std::vector<float> vertices);
	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() {}

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual uint32_t GetCount() const = 0;

		static IndexBuffer* Create(std::vector<uint32_t> indices);
	};
}
