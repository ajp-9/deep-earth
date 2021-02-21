#include "ChunkDatabase.hpp"

#include <iostream>

void ChunkDatabase::addChunk(std::shared_ptr<Chunk> chunk)
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

bool ChunkDatabase::addNode(Node node, glm::vec3 specificPosition)
{
	glm::ivec3 nodePosition = glm::ivec3((int)std::floor(specificPosition.x + .5f),
										 (int)std::floor(specificPosition.y + .5f),
										 (int)std::floor(specificPosition.z + .5f));

	glm::ivec3 chunkPosition = glm::ivec3((int)std::floor(float(nodePosition.x) / float((CHUNK_SIZE))),
									      (int)std::floor(float(nodePosition.y) / float((CHUNK_SIZE))),
									      (int)std::floor(float(nodePosition.z) / float((CHUNK_SIZE))));

	glm::ivec3 inChunkNodePosition = glm::ivec3(nodePosition.x - (chunkPosition.x * (CHUNK_SIZE)),
												nodePosition.y - (chunkPosition.y * (CHUNK_SIZE)),
												nodePosition.z - (chunkPosition.z * (CHUNK_SIZE)));

	std::weak_ptr<Chunk> chunk;
	getChunkWCallback(chunkPosition, chunk);

	// If chunk doesn't exist...
	if (!chunk.expired())
	{
		// If block isn't air...
		if (chunk.lock()->getNode(inChunkNodePosition).m_ID == node::air)
		{
			chunk.lock()->addNode(node, inChunkNodePosition);

			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		std::vector<std::pair<Node, glm::ivec3>> nodes = { std::make_pair(node, inChunkNodePosition) };
		auto chunk = std::make_shared<Chunk>(chunkPosition, nodes, m_NodeManager, *this);
		addChunk(chunk);

		return true;
	}
}

bool ChunkDatabase::removeNode(glm::vec3 specificPosition)
{
	glm::ivec3 nodePosition = glm::ivec3((int)std::floor(specificPosition.x + .5f),
										 (int)std::floor(specificPosition.y + .5f),
										 (int)std::floor(specificPosition.z + .5f));

	glm::ivec3 chunkPosition = glm::ivec3((int)std::floor(float(nodePosition.x) / float((CHUNK_SIZE))),
										  (int)std::floor(float(nodePosition.y) / float((CHUNK_SIZE))),
										  (int)std::floor(float(nodePosition.z) / float((CHUNK_SIZE))));

	glm::ivec3 inChunkNodePosition = glm::ivec3(nodePosition.x - (chunkPosition.x * (CHUNK_SIZE)),
												nodePosition.y - (chunkPosition.y * (CHUNK_SIZE)),
												nodePosition.z - (chunkPosition.z * (CHUNK_SIZE)));

	std::weak_ptr<Chunk> chunk;
	getChunkWCallback(chunkPosition, chunk);

	if (!chunk.expired())
	{
		if (chunk.lock()->getNode(inChunkNodePosition).m_ID != node::air)
		{
			chunk.lock()->removeNode(inChunkNodePosition);

			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

const Node ChunkDatabase::getNode(glm::vec3 specificPosition)
{
	glm::ivec3 nodePosition = glm::ivec3((int)std::floor(specificPosition.x + .5f),
										 (int)std::floor(specificPosition.y + .5f), 
										 (int)std::floor(specificPosition.z + .5f));

	glm::ivec3 chunkPosition = glm::ivec3((int)std::floor(float(nodePosition.x) / float((CHUNK_SIZE))),
										  (int)std::floor(float(nodePosition.y) / float((CHUNK_SIZE))),
										  (int)std::floor(float(nodePosition.z) / float((CHUNK_SIZE))));

	glm::ivec3 inChunkNodePosition = glm::ivec3(nodePosition.x - (chunkPosition.x * (CHUNK_SIZE)),
												nodePosition.y - (chunkPosition.y * (CHUNK_SIZE)),
												nodePosition.z - (chunkPosition.z * (CHUNK_SIZE)));

	std::weak_ptr<Chunk> chunk;
	getChunkWCallback(chunkPosition, chunk);

	if (!chunk.expired())
		return chunk.lock()->getNode(inChunkNodePosition);
	else
		return Node(node::air);
}

const Node ChunkDatabase::getNode(glm::ivec3 nodePosition)
{
	glm::ivec3 chunkPosition = glm::ivec3((int)std::floor(float(nodePosition.x) / float((CHUNK_SIZE))),
		(int)std::floor(float(nodePosition.y) / float((CHUNK_SIZE))),
		(int)std::floor(float(nodePosition.z) / float((CHUNK_SIZE))));

	glm::ivec3 inChunkNodePosition = glm::ivec3(nodePosition.x - (chunkPosition.x * (CHUNK_SIZE)),
		nodePosition.y - (chunkPosition.y * (CHUNK_SIZE)),
		nodePosition.z - (chunkPosition.z * (CHUNK_SIZE)));

	std::weak_ptr<Chunk> chunk;
	getChunkWCallback(chunkPosition, chunk);

	if (!chunk.expired())
		return chunk.lock()->getNode(inChunkNodePosition);
	else
		return Node(node::air);
}

void ChunkDatabase::addChunkMeshToQueue(glm::ivec3 position, bool buildNeighbors)
{
	auto it = std::find_if(m_ChunkMeshesQueue.begin(), m_ChunkMeshesQueue.end(), [&position](std::pair<glm::ivec3, bool>& val) { return val.first == position; });
	if (it == m_ChunkMeshesQueue.end())
	{
		m_ChunkMeshesQueue.push_back(std::make_pair(position, buildNeighbors));
	}
}

void ChunkDatabase::buildChunkMeshFromQueue()
{
	if (m_ChunkMeshesQueue.size())
	{
		auto& [position, buildNeighbors] = m_ChunkMeshesQueue.back();

		m_ChunkMeshesQueue.pop_back();

		if (m_ChunkHash.find(position) != m_ChunkHash.end())
		{
			m_ChunkHash[position].lock()->buildMesh(buildNeighbors);
		}
		else
		{
			addChunk(std::make_shared<Chunk>(position, m_NodeManager, *this, true));
		}
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

std::weak_ptr<Chunk>& ChunkDatabase::getChunk(glm::ivec3 position)
{
	if (m_ChunkHash.size())
	{
		if (m_ChunkHash.find(position) != m_ChunkHash.end())
		{
			return m_ChunkHash[position];
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
