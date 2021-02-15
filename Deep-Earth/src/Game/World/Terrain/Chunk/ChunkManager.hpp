#pragma once

#include "Chunk.hpp"
#include "ChunkDatabase.hpp"
#include "ChunkDatabaseNEW.hpp"

class ChunkManager
{
public:

	ChunkManager();

	void loadChunks(NodeManager& nodeManager, glm::ivec3 playerPos);

	void render(engine::Shader3D& shader);
	void update();
	void tick();

private:

	ChunkDatabase m_ChunkDatabase;
	ChunkDatabaseNEW NEW;
};
