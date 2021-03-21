#include "Terrain.hpp"

Terrain::Terrain()
	: m_ChunkManager(m_NodeManager), m_WorldGenerator(0, m_NodeManager, m_ChunkManager)
{}

void Terrain::render(engine::Shader3D& shader)
{
	m_NodeManager.bindTextures();
	m_ChunkManager.render(shader);
}

void Terrain::update(glm::vec3& playerPos)
{
	if (m_PlayerLastChunkPos != m_ChunkManager.getChunkPositionFromVec3(playerPos))
	{
		m_PlayerLastChunkPos = m_ChunkManager.getChunkPositionFromVec3(playerPos);

		loadChunks(playerPos);
		unloadChunks(playerPos);
	}
}

void Terrain::loadChunks(glm::vec3& playerPos)
{
	for (int x = m_PlayerLastChunkPos.x - VIEW_DISTANCE; x < m_PlayerLastChunkPos.x + VIEW_DISTANCE; x++)
		for (int y = m_PlayerLastChunkPos.y - VIEW_DISTANCE; y < m_PlayerLastChunkPos.y + VIEW_DISTANCE; y++)
			for (int z = 0; z < 1; z++)
			{
				if (!m_ChunkManager.hasChunk(glm::ivec3(x, y, z)))
				{
					m_WorldGenerator.generateChunk(glm::ivec3(x, y, z)); // generation is the problem, make a queue
				}
			}
}

void Terrain::unloadChunks(glm::vec3& playerPos)
{

}
