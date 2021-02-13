#include "ChunkManager.hpp"

#include "../Node/NodeManager.hpp"

#define PROFILE
#include "../../../../Engine/Util/Profile.hpp"

ChunkManager::ChunkManager(NodeManager& nodeManager)
{
	for (int x = 0; x < 5; x++)
		for (int y = 0; y < 5; y++)
			for (int z = 0; z < 2; z++)
			{
				chunks.emplace_back(std::make_unique<Chunk>(nodeManager, glm::ivec3(x, y, z)));
			}
}

void ChunkManager::render(engine::Shader3D& shader)
{
	for (auto& chunk : chunks)
		chunk->render(shader);
}

void ChunkManager::update()
{

}

void ChunkManager::tick()
{
	
}