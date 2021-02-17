#include "ChunkDatabase.hpp"

void ChunkDatabase::addChunk(std::shared_ptr<Chunk>& chunk)
{
	m_Chunks.emplace_back(chunk);
	m_ChunkHash[chunk->getPosition()] = chunk;
}

void ChunkDatabase::removeChunk(glm::ivec3 position)
{
	auto it = std::find_if(m_Chunks.begin(), m_Chunks.end(), [&position](std::shared_ptr<Chunk>& val) { return val->getPosition() == position; });
	if (it != m_Chunks.end())
	{
		m_Chunks.erase(it);
		m_ChunkHash.erase(position);
	}
	else
	{
		std::cout << "ERROR::<ChunkDatabase::removeChunk()>: Can't find chunk!\n";
	}
}

void ChunkDatabase::addChunkMeshToQueue(glm::ivec3 position, bool buildNeighbors)
{
	m_ChunkMeshesQueue.emplace(std::make_pair(position, buildNeighbors));
}

void ChunkDatabase::buildChunkMeshFromQueue()
{
	if (m_ChunkMeshesQueue.size())
	{
		auto& [position, buildNeighbors] = m_ChunkMeshesQueue.front();

		if (m_ChunkHash.find(position) != m_ChunkHash.end())
		{
			m_ChunkHash[position].lock()->buildMesh(buildNeighbors);
		}

		m_ChunkMeshesQueue.pop();
	}
}

void ChunkDatabase::getChunkWCallback(glm::ivec3 position, std::weak_ptr<Chunk>& chunk)
{
	if (m_ChunkHash.size())
	{
		if (m_ChunkHash.find(position) != m_ChunkHash.end())
		{
			chunk = m_ChunkHash[position];
		}
	}
}

bool ChunkDatabase::hasChunk(glm::vec3 position)
{
	if (m_ChunkHash.find(position) != m_ChunkHash.end())
		return true;
	else
		return false;
}
