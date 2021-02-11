#pragma once

#include "Chunk.hpp"

class ChunkStack
{
public:

private:

	std::vector<std::unique_ptr<Chunk>> m_Chunks;
};