#pragma once

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/hash.hpp>
#include <unordered_map>
#include <queue>

#include "Chunk.hpp"

class ChunkDatabase
{
public:

	~ChunkDatabase()
	{
		m_ChunkHash.clear();
		m_Chunks.clear();
	}

	void addChunk(std::shared_ptr<Chunk>& chunk);
	void removeChunk(glm::ivec3 position);

	// Adds a chunk position to the queue of chunk meshes to build. 
	void addChunkMeshToQueue(glm::ivec3 position, bool buildNeighbors);
	void buildChunkMeshFromQueue();

	//std::weak_ptr<Chunk>& getChunk(glm::ivec3 position);
	void getChunkWCallback(glm::ivec3 position, std::weak_ptr<Chunk>& chunk);

	bool hasChunk(glm::vec3 position);

	std::vector<std::shared_ptr<Chunk>>& getAllChunks() { return m_Chunks; }


	std::vector<std::shared_ptr<Chunk>> m_Chunks;
	// Fast way of finding a chunk from position.
	std::unordered_map<glm::ivec3, std::weak_ptr<Chunk>> m_ChunkHash;

	std::queue<std::pair<glm::ivec3, bool>> m_ChunkMeshesQueue;
};
