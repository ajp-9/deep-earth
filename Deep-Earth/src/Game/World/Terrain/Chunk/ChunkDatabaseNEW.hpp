#pragma once

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/hash.hpp>
#include <unordered_map>
#include <entt.hpp>
#include <queue>

#include "Chunk.hpp"

struct ChunkDatabaseNEW
{
	~ChunkDatabaseNEW()
	{
		m_ChunkHash.clear();
	}

	inline void addChunk(std::shared_ptr<Chunk>& chunk)
	{
		m_Chunks.emplace_back(chunk);
		m_ChunkHash[chunk->getPosition()] = chunk;
	}

	inline void removeChunk(glm::ivec3 position)
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

	inline std::weak_ptr<Chunk>& getChunk(glm::ivec3 position)
	{
		if (m_ChunkHash.find(position) != m_ChunkHash.end())
		{
			return m_ChunkHash.at(position);
		}
	}

	inline void getChunkWCallback(glm::ivec3 position, std::weak_ptr<Chunk>& chunk)
	{
		if (m_ChunkHash.size())
		{
			if (m_ChunkHash.find(position) != m_ChunkHash.end())
			{
				chunk = m_ChunkHash.at(position);
			}
		}
	}

	inline bool hasChunk(glm::vec3 position)
	{
		if (m_ChunkHash.find(position) != m_ChunkHash.end())
			return true;
		else
			return false;
	}

	std::vector<std::shared_ptr<Chunk>> m_Chunks;
	// Fast way of finding a chunk from position.
	std::unordered_map<glm::ivec3, std::weak_ptr<Chunk>> m_ChunkHash;

	std::queue<glm::ivec3> m_ChunkBuildMeshQueue;
};
