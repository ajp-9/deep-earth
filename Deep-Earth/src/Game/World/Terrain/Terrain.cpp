#include "Terrain.hpp"

Terrain::Terrain()
	: m_ChunkManager(m_NodeManager), m_Atlas("res/textures/atlas.png"), m_WorldGenerator(0, m_NodeManager, m_ChunkManager)
{}

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
		for (int x = (playerPos.x / 32) - VIEW_DISTANCE; x < (playerPos.x / 32) + VIEW_DISTANCE; x++)
			for (int y = (playerPos.y / 32) - VIEW_DISTANCE; y < (playerPos.y / 32) + VIEW_DISTANCE; y++)
				for (int z = 0; z < 1; z++)
				{
					if (!m_ChunkManager.hasChunk(glm::ivec3(x, y, z)))
					{
						m_WorldGenerator.generateChunk(glm::ivec3(x, y, z));
					}
				}

		i = 0;
	}
}
