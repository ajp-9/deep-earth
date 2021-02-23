#include "WorldGenerator.hpp"

WorldGenerator::WorldGenerator(uint32_t seed, ChunkManager& chunkManager)
	: c_Seed(seed), m_ChunkManager(chunkManager)
{
}

void WorldGenerator::generateChunk(glm::ivec3 position)
{
}
