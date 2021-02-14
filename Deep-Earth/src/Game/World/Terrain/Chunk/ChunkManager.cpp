#include "ChunkManager.hpp"

#include "../Node/NodeManager.hpp"
#include <algorithm>
#define PROFILE
#include "../../../../Engine/Util/Profile.hpp"

ChunkManager::ChunkManager(NodeManager& nodeManager)
{
	for (int x = 0; x < 4; x++)
		for (int y = 0; y < 4; y++)
			for (int z = 0; z < 2; z++)
			{
				std::shared_ptr<Chunk> chunk = std::make_shared<Chunk>(nodeManager, glm::ivec3(x, y, z), m_ChunkDatabase);
				m_ChunkDatabase.addChunk(chunk);
			}

	for (auto& c : m_ChunkDatabase.m_Chunks)
	{
		PROFILE_SCOPE("w", w);
		c->getNeighboringChunks();
	}

	auto ps = glm::ivec3(0, 0, 0);
	m_ChunkDatabase.eraseChunk(ps);
}

void ChunkManager::render(engine::Shader3D& shader)
{
	for (auto& chunk : m_ChunkDatabase.m_Chunks)
		chunk->render(shader);
}

void ChunkManager::update()
{

}

void ChunkManager::tick()
{
	
}
