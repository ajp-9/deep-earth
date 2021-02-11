#pragma once

#include "../../../Engine/Renderer/Model/Texture/Texture.hpp"
#include "Chunk/ChunkManager.hpp"
#include "Block/BlockManager.hpp"

class Terrain
{
public:

	Terrain();

	void render(engine::Shader3D& shader);
	void update();

private:

	BlockManager m_BlockManager;
	ChunkManager m_ChunkManager;

	engine::Texture m_Atlas;
};