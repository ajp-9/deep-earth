#include "ChunkManager.hpp"

#include "../Node/NodeManager.hpp"
#include <iostream>
#define PROFILE
#include "../../../../Engine/Util/Profile.hpp"

#define VIEW_DISTANCE 6

void ChunkManager::loadChunks(NodeManager& nodeManager, glm::vec3 playerPos)
{
	for (int x = (playerPos.x / 32) - VIEW_DISTANCE; x < (playerPos.x / 32) + VIEW_DISTANCE; x++) 
		for (int y = (playerPos.y / 32) - VIEW_DISTANCE; y < (playerPos.y / 32) + VIEW_DISTANCE; y++) 
			for (int z = 0; z < 1; z++)
			{
				if (!m_ChunkDatabase.hasChunk(glm::ivec3(x, y, z)))
				{
					std::shared_ptr<Chunk> chunk = std::make_shared<Chunk>(glm::ivec3(x, y, z), nodeManager, m_ChunkDatabase);
					m_ChunkDatabase.addChunk(chunk);
					m_ChunkDatabase.addChunkMeshToQueue(glm::ivec3(x, y, z), true);
				}
			}
}

void ChunkManager::render(engine::Shader3D& shader)
{	
	for (auto& chunk : m_ChunkDatabase.getAllChunks())
		chunk->render(shader);

	printf("%u\n", m_ChunkDatabase.m_ChunkMeshesQueue.size());

	m_ChunkDatabase.buildChunkMeshFromQueue();
	m_ChunkDatabase.buildChunkMeshFromQueue();
	m_ChunkDatabase.buildChunkMeshFromQueue();
}

void ChunkManager::update()
{

}

void ChunkManager::tick()
{
	
}
