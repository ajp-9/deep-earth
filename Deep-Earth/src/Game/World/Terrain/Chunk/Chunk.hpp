#pragma once

#include "../Node/Raw/Node.hpp"
#include "../Light/Light.hpp"
#include "../../../../Engine/OpenGL/VertexArray.hpp"
#include "../../../../Engine/Renderer/Shader/Shader3D.hpp"
#include "../Node/NodeManager.hpp"
#include "../../../../Engine/Util/Math.hpp"
#include <iostream>

#define CHUNK_SIZE 32
#define CHUNK_VOLUME 32768 // 32*32*32

struct ChunkDatabase;
struct ChunkDatabaseNEW;

class Chunk
{
public:

	Chunk(NodeManager& nodeManager, glm::ivec3 position, ChunkDatabaseNEW& chunkDatabase);
	Chunk(NodeManager& nodeManager, std::vector<Node>& m_Blocks, glm::ivec3& position, ChunkDatabaseNEW& chunkDatabase);

	void render(engine::Shader3D& shader);
	void tick();

	Node& getNode(glm::ivec3 position);
	void setNode(glm::ivec3 position, uint id);
	
	inline const glm::ivec3& getPosition() { return m_Position; }

	void getNeighboringChunks();


	// Run after ALL chunks have been loaded.
	void buildMesh(NodeManager& nodeManager, bool buildNeighbors = true);

private:

	glm::ivec3 m_Position;

	std::unique_ptr<engine::gl::VertexArray> m_VertexArray;

	glm::mat4 m_TransformationMatrix;

	//ChunkDatabase& m_ChunkDatabase;
	ChunkDatabaseNEW& NEW;

	std::weak_ptr<Chunk> m_ChunkRef_front;			bool m_IsChunkActive_front = false;
	std::weak_ptr<Chunk> m_ChunkRef_frontRight;		bool m_IsChunkActive_frontRight = false;
	std::weak_ptr<Chunk> m_ChunkRef_back;			bool m_IsChunkActive_back = false;
	std::weak_ptr<Chunk> m_ChunkRef_frontLeft;		bool m_IsChunkActive_frontLeft = false;
	std::weak_ptr<Chunk> m_ChunkRef_top;			bool m_IsChunkActive_top = false;
	std::weak_ptr<Chunk> m_ChunkRef_bottom;			bool m_IsChunkActive_bottom = false;

	std::vector<Node> m_Nodes = std::vector<Node>(CHUNK_VOLUME);
	std::vector<Light> m_LightMap = std::vector<Light>(CHUNK_VOLUME);
};