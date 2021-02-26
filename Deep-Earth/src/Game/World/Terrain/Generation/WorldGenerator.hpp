#pragma once

#include <glm/vec3.hpp>

#include "../Chunk/ChunkManager.hpp"

class WorldGenerator
{
public:

	WorldGenerator(uint32_t seed, NodeManager& nodeManager, ChunkManager& chunkManager);

	void generateChunk(glm::ivec3 position);

private:

	NodeManager& m_NodeManager;
	ChunkManager& m_ChunkManager;

	const uint32_t c_Seed;
};
