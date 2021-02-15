 #include "ChunkManager.hpp"

#include "../Node/NodeManager.hpp"
#include <algorithm>
#define PROFILE
#include "../../../../Engine/Util/Profile.hpp"

#define VIEW_DISTANCE 5

ChunkManager::ChunkManager()
{}

void ChunkManager::loadChunks(NodeManager& nodeManager, glm::ivec3 playerPos)
{
	for (int x = (playerPos.x / 32) - VIEW_DISTANCE; x < (playerPos.x / 32) + VIEW_DISTANCE; x++)
		for (int y = (playerPos.y / 32) - VIEW_DISTANCE; y < (playerPos.y / 32) + VIEW_DISTANCE; y++)
			for (int z = 0; z < 1; z++)
			{
				if (!NEW.hasChunk(glm::ivec3(x, y, z)))
				{
					std::shared_ptr<Chunk> chunk = std::make_shared<Chunk>(nodeManager, glm::ivec3(x, y, z), NEW);
					NEW.addChunk(chunk);
					chunk->buildMesh(nodeManager);
				}
			}

	std::cout << "-------------------\n";

	//std::shared_ptr<Chunk> chunk = std::make_shared<Chunk>(nodeManager, glm::ivec3(0, 0, 0), NEW);
	//NEW.addChunk(chunk);

	//for (auto& c : NEW.m_Chunks)
	//	c->buildMesh(nodeManager);
}

void ChunkManager::render(engine::Shader3D& shader)
{
	for (auto& chunk : NEW.m_Chunks)
		chunk->render(shader);
}

void ChunkManager::update()
{

}

void ChunkManager::tick()
{
	
}
