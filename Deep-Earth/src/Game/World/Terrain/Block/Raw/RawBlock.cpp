#include "RawBlock.hpp"

RawBlock::RawBlock()
	: m_ID(0) // air
{}

RawBlock::RawBlock(byte id)
	: m_ID(id)
	, m_Data(0)
{}
