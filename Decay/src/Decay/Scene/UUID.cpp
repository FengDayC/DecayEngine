#include "UUID.h"

Decay::UUID::UUID()
{
	m_UUID = -1;
}

Decay::UUID::UUID(uint64_t uuid)
{
	m_UUID = uuid;
}

Decay::UUID::UUID(UUID& other)
{
	m_UUID = other.m_UUID;
}

