#pragma once

#include "Chunk.hpp"

struct ChunkDatabase
{
	inline void addChunk(std::shared_ptr<Chunk>& chunk)
	{
		m_Chunks.push_back(chunk);
	}

	inline void eraseChunk(glm::ivec3& position)
	{
		auto it = std::find_if(m_Chunks.begin(), m_Chunks.end(), [&position](std::shared_ptr<Chunk>& val) { return val->getPosition() == position; });
		if (it != m_Chunks.end())
			m_Chunks.erase(it);
		else
			std::cout << "ERROR::<ChunkDatabase::eraseChunk()>: Can't find chunk!\n";
	}

	inline std::shared_ptr<Chunk>& getChunk(glm::ivec3 position)
	{
		auto it = std::find_if(m_Chunks.begin(), m_Chunks.end(), [&position](std::shared_ptr<Chunk>& val) { return val->getPosition() == position; });
		return m_Chunks.at(std::distance(m_Chunks.begin(), it));
	}

	inline void getChunkWCallback(glm::ivec3 position, std::weak_ptr<Chunk>& senderChunk)
	{
		auto it = std::find_if(m_Chunks.begin(), m_Chunks.end(), [&position](std::shared_ptr<Chunk>& val) { return val->getPosition() == position; });

		if (it != m_Chunks.end())
			senderChunk = m_Chunks.at(std::distance(m_Chunks.begin(), it));
	}

	// Is a shared ptr for space & weak_ptrs
	std::vector<std::shared_ptr<Chunk>> m_Chunks;
};
