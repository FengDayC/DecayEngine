#include "UUID.h"

Decay::UUID::UUID()
{
	m_uuid = -1;
}

Decay::UUID::UUID(uint64_t uuid)
{
	m_uuid = uuid;
}

Decay::UUID::UUID(UUID& other)
{
	m_uuid = other.m_uuid;
}

