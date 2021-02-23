#include "ChunkManager.hpp"

#include "../Node/NodeManager.hpp"
#include <iostream>
#define PROFILE
#include "../../../../Engine/Util/Profile.hpp"

#define VIEW_DISTANCE 6

void ChunkManager::loadChunks(NodeManager& nodeManager, glm::vec3 playerPos)
{
	for (int x = (playerPos.x / 32) - VIEW_DISTANCE; x < (playerPos.x / 32) + VIEW_DISTANCE; x++) 
		for (int y = (playerPos.y / 32) - VIEW_DISTANCE; y < (playerPos.y / 32) + VIEW_DISTANCE; y++) 
			for (int z = 0; z < 1; z++)
			{
				if (!hasChunk(glm::ivec3(x, y, z)))
				{
					std::shared_ptr<Chunk> chunk = std::make_shared<Chunk>(glm::ivec3(x, y, z), nodeManager, *this);
					addChunk(chunk);
					addChunkMeshToQueue(glm::ivec3(x, y, z), true);
				}
			}
}

void ChunkManager::render(engine::Shader3D& shader)
{	
	for (auto& chunk : m_Chunks)
		chunk->render(shader);

	printf("%u\n", m_ChunkMeshesQueue.size());

	buildChunkMeshFromQueue();
	buildChunkMeshFromQueue();
	buildChunkMeshFromQueue();
}

void ChunkManager::update()
{

}

void ChunkManager::tick()
{
	
}

void ChunkManager::addChunk(std::shared_ptr<Chunk> chunk)
{
	m_Chunks.emplace_back(chunk);
	m_ChunkHash[chunk->getPosition()] = chunk;
}

void ChunkManager::removeChunk(glm::ivec3 position)
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

bool ChunkManager::addNode(Node node, glm::vec3 specificPosition)
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
		//auto chunk = std::make_shared<Chunk>(chunkPosition, nodes, m_NodeManager, *this);
		//addChunk(chunk);

		return true;
	}
}

bool ChunkManager::removeNode(glm::vec3 specificPosition)
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

const Node ChunkManager::getNode(glm::vec3 specificPosition)
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

const Node ChunkManager::getNode(glm::ivec3 nodePosition)
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

void ChunkManager::addChunkMeshToQueue(glm::ivec3 position, bool buildNeighbors)
{
	auto it = std::find_if(m_ChunkMeshesQueue.begin(), m_ChunkMeshesQueue.end(), [&position](std::pair<glm::ivec3, bool>& val) { return val.first == position; });
	if (it == m_ChunkMeshesQueue.end())
	{
		m_ChunkMeshesQueue.push_back(std::make_pair(position, buildNeighbors));
	}
}

void ChunkManager::buildChunkMeshFromQueue()
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

void ChunkManager::getChunkWCallback(glm::ivec3 position, std::weak_ptr<Chunk>& chunk)
{
	if (m_ChunkHash.size())
	{
		if (m_ChunkHash.find(position) != m_ChunkHash.end())
		{
			chunk = m_ChunkHash[position];
		}
	}
}

std::weak_ptr<Chunk>& ChunkManager::getChunk(glm::ivec3 position)
{
	if (m_ChunkHash.size())
	{
		if (m_ChunkHash.find(position) != m_ChunkHash.end())
		{
			return m_ChunkHash[position];
		}
	}
}

bool ChunkManager::hasChunk(glm::vec3 position)
{
	if (m_ChunkHash.find(position) != m_ChunkHash.end())
		return true;
	else
		return false;
}
