#include "Terrain.hpp"

Terrain::Terrain()
	: m_ChunkManager(m_NodeManager), m_Atlas("res/textures/atlas.png")
{
	m_ChunkManager.loadChunks(m_NodeManager, glm::ivec3(0));
}

void Terrain::render(engine::Shader3D& shader)
{
	m_Atlas.bind();
	m_ChunkManager.render(shader);
}

void Terrain::update(glm::vec3& playerPos)
{
	loadNUnloadChunks(playerPos);
}

void Terrain::loadNUnloadChunks(glm::vec3& playerPos)
{
	static uint i = 0;
	i++;
	if (i == 5)
	{
		m_ChunkManager.loadChunks(m_NodeManager, playerPos);
		i = 0;
	}
}
