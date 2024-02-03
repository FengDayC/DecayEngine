#include "UUID.h"

uint64_t Decay::UUID::s_uuidCnt = -1;

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

uint64_t Decay::UUID::GetNewUUID()
{
	return ++s_uuidCnt;
}

