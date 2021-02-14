#pragma once

#include "Chunk.hpp"
#include "ChunkDatabase.hpp"

class ChunkManager
{
public:

	ChunkManager(NodeManager& nodeManager);

	void render(engine::Shader3D& shader);
	void update();
	void tick();

private:

	ChunkDatabase m_ChunkDatabase;
};
