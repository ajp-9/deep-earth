#pragma once

#include "Chunk.hpp"
#include "ChunkDatabase.hpp"

class ChunkManager
{
public:

	ChunkManager(NodeManager& nodeManager) : m_ChunkDatabase(nodeManager) {}

	void loadChunks(NodeManager& nodeManager, glm::vec3 playerPos);

	void render(engine::Shader3D& shader);
	void update();
	void tick();

	// For player placing blocks
	// Returns true for successful
	inline bool addNode(Node node, glm::vec3 specificPosition) { return m_ChunkDatabase.addNode(node, specificPosition); }
	// Sets node to air
	// Returns true for successful
	inline bool removeNode(glm::vec3 specificPosition) { return m_ChunkDatabase.removeNode(specificPosition); }

	const Node getNode(glm::vec3 specificPosition) { return m_ChunkDatabase.getNode(specificPosition); }
	const Node getNode(glm::ivec3 nodePosition) { return m_ChunkDatabase.getNode(nodePosition); }

private:

	ChunkDatabase m_ChunkDatabase;
};
