#pragma once

#include "../../../Engine/Renderer/Model/Texture/Texture.hpp"
#include "Chunk/ChunkManager.hpp"
#include "Node/NodeManager.hpp"
#include "Generation/WorldGenerator.hpp"

#define VIEW_DISTANCE 6

class Terrain
{
public:

	Terrain();

	void render(engine::Shader3D& shader);
	void update(glm::vec3& playerPos);

	void loadNUnloadChunks(glm::vec3& playerPos);

	inline ChunkManager& getChunkManager() { return m_ChunkManager; }

private:

	WorldGenerator m_WorldGenerator;

	NodeManager m_NodeManager;
	ChunkManager m_ChunkManager;

	engine::Texture m_Atlas;
};
