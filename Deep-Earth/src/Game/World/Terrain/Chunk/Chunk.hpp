#pragma once

#include "../Node/Raw/Node.hpp"
#include "../Light/Light.hpp"
#include "../../../../Engine/OpenGL/VertexArray.hpp"
#include "../../../../Engine/Renderer/Shader/Shader3D.hpp"
#include "../Node/NodeManager.hpp"

#define CHUNK_SIZE 32
#define CHUNK_VOLUME 32768 // 32*32*32

class ChunkDatabase;

class Chunk
{
public:

	// Blank chunk
	Chunk(glm::ivec3 position, NodeManager& nodeManager, ChunkDatabase& chunkDatabase, bool empty = false);
	// Everything already packaged up.
	Chunk(glm::ivec3& position, std::vector<Node>& nodes, NodeManager& nodeManager, ChunkDatabase& chunkDatabase);
	// Unpacked nodes thrown at random.
	Chunk(glm::ivec3& position, std::vector<std::pair<Node, glm::ivec3>>& nodes, NodeManager& nodeManager, ChunkDatabase& chunkDatabase);
	~Chunk();

	void render(engine::Shader3D& shader);
	void tick();

	// For player placing blocks
	void addNode(Node& node, glm::ivec3 nodePosition);
	// Sets node to air
	void removeNode(glm::ivec3 nodePosition);

	const Node getNode(glm::ivec3 nodePosition) const;
	void setNode(Node node, glm::ivec3 nodePosition);

	inline const glm::ivec3& getPosition() const { return m_Position; }

	void getNeighboringChunks(bool buildingMesh = false);

	// Run after ALL chunks have been loaded.
	void buildMesh(bool buildNeighbors);

private:

	glm::ivec3 m_Position;

	std::unique_ptr<engine::gl::VertexArray> m_VertexArray;

	glm::mat4 m_TransformationMatrix;

	ChunkDatabase& m_ChunkDatabase;
	NodeManager& m_NodeManager;

	std::weak_ptr<Chunk> m_ChunkRef_front;     	 bool m_MeshSawMy_front = false;
	std::weak_ptr<Chunk> m_ChunkRef_frontRight;	 bool m_MeshSawMy_frontRight = false;
	std::weak_ptr<Chunk> m_ChunkRef_back;		 bool m_MeshSawMy_back = false;
	std::weak_ptr<Chunk> m_ChunkRef_frontLeft;	 bool m_MeshSawMy_frontLeft = false;
	std::weak_ptr<Chunk> m_ChunkRef_top;		 bool m_MeshSawMy_top = false;
	std::weak_ptr<Chunk> m_ChunkRef_bottom;		 bool m_MeshSawMy_bottom = false;

	std::vector<Node> m_Nodes = std::vector<Node>(CHUNK_VOLUME);
	std::vector<Light> m_LightMap = std::vector<Light>(CHUNK_VOLUME);
};