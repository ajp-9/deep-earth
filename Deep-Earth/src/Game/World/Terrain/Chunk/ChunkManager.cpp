#include "ChunkManager.hpp"

#include "../Block/BlockManager.hpp"

ChunkManager::ChunkManager(BlockManager& blockManager)
{
	for (int x = 0; x < 2; x++)
		for (int y = 0; y < 2; y++)
			for (int z = 0; z < 2; z++)
				chunks.emplace_back(std::make_unique<Chunk>(blockManager, glm::ivec3(x, y, z)));	
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