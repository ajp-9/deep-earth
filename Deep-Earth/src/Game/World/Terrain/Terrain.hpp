#pragma once

#include "../../../Engine/Renderer/Model/Texture/Texture.hpp"
#include "Chunk/ChunkManager.hpp"
#include "Node/NodeManager.hpp"
#include "Generation/WorldGenerator.hpp"

class Terrain
{
public:

	Terrain();

	void render(engine::Shader3D& shader);
	void update(glm::vec3& playerPos);

	void loadNUnloadChunks(glm::vec3& playerPos);

	inline ChunkManager& getChunkManager() { return m_ChunkManager; }

private:

	NodeManager m_NodeManager;
	ChunkManager m_ChunkManager;

	engine::Texture m_Atlas;
};
