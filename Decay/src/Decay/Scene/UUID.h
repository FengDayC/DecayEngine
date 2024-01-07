#pragma once

namespace Decay
{
	class UUID
	{
	public:

		UUID();
		UUID(uint64_t uuid);
		UUID(UUID& other);
		inline operator uint64_t() const { return m_uuid; }
		inline operator const uint64_t() { return m_uuid; }
		inline operator bool() const { return m_uuid != -1; }
	private:

		uint64_t m_uuid;
	};
}