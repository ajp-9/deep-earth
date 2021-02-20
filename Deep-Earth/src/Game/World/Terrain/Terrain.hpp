#pragma once

#include "../../../Engine/Renderer/Model/Texture/Texture.hpp"
#include "Chunk/ChunkManager.hpp"
#include "Node/NodeManager.hpp"

class Terrain
{
public:

	Terrain();

	void render(engine::Shader3D& shader, glm::vec3& playerPos);
	void update();

	inline ChunkManager& getChunkManager() { return m_ChunkManager; }

private:

	NodeManager m_NodeManager;
	ChunkManager m_ChunkManager;

	engine::Texture m_Atlas;
};
