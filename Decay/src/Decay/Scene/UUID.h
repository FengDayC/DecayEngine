#pragma once

namespace Decay
{
	class UUID
	{
	public:

		UUID();
		UUID(uint64_t uuid);
		UUID(UUID& other);
		inline operator uint64_t() const { return m_UUID; }
		inline operator const uint64_t() { return m_UUID; }
		inline operator bool() const { return m_UUID != -1; }

	public:
		static uint64_t GetNewUUID();

	private:

		uint64_t m_UUID;

		static uint64_t s_uuidCnt;
	};
}