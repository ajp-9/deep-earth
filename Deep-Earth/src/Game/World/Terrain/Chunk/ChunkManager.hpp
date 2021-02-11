#pragma once

#include "Chunk.hpp"

class ChunkManager
{
public:

	ChunkManager(NodeManager& nodeManager);

	void render(engine::Shader3D& shader);
	void update();
	void tick();

private:

	// Is a unique ptr for space
	std::vector<std::unique_ptr<Chunk>> chunks;
};