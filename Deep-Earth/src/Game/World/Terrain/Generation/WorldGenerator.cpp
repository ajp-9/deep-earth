#include "WorldGenerator.hpp"

#include <glm/gtc/noise.hpp>
#include <iostream>

WorldGenerator::WorldGenerator(uint32_t seed, NodeManager& nodeManager, ChunkManager& chunkManager)
	: c_Seed(seed),m_NodeManager(nodeManager), m_ChunkManager(chunkManager)
{}

void WorldGenerator::generateChunk(glm::ivec3 position)
{
	std::shared_ptr<Chunk> chunk = std::make_shared<Chunk>(position, m_NodeManager, m_ChunkManager, true);

	for (uint x = 0; x < CHUNK_SIZE; x++)
	{
		for (uint y = 0; y < CHUNK_SIZE; y++)
		{
			for (uint z = 0 ; z < glm::simplex(glm::vec2((x + (position.x * CHUNK_SIZE)) * .02, (y + (position.y * CHUNK_SIZE)) * .02)) * 6 + 8; z++)
			{
				chunk->setNode(node::grass, glm::ivec3(x, y, z));
			}
		}
	}


	std::cout << (int) 5 * glm::perlin(glm::vec3(7, 5, c_Seed * 2)) * 5 << std::endl;
	m_ChunkManager.addChunk(chunk);
}
