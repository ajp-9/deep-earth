#include "ChunkManager.hpp"

#include "../Node/NodeManager.hpp"
#include <algorithm>
#define PROFILE
#include "../../../../Engine/Util/Profile.hpp"

ChunkManager::ChunkManager(NodeManager& nodeManager)
{
	for (int x = 0; x < 24; x++)
		for (int y = 0; y < 24; y++)
			for (int z = 0; z < 1; z++)
			{
				std::shared_ptr<Chunk> chunk = std::make_shared<Chunk>(nodeManager, glm::ivec3(x, y, z), m_ChunkDatabase.m_Chunks);
				m_ChunkDatabase.addChunk(chunk);
			}

	auto ps = glm::ivec3(23, 23, 1);
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
