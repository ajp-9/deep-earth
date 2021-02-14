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

class Chunk
{
public:

	Chunk(NodeManager& nodeManager, glm::ivec3 position, std::vector<std::shared_ptr<Chunk>>& allChunksRef);
	Chunk(NodeManager& nodeManager, std::vector<Node>& m_Blocks, glm::ivec3& position, std::vector<std::shared_ptr<Chunk>>& allChunksRef);

	void render(engine::Shader3D& shader);
	void tick();

	Node getNode(glm::ivec3 position);
	void setNode(glm::ivec3 position, uint id);

	inline const glm::ivec3& getPosition() { return m_Position; }

private:

	void buildMesh(NodeManager& nodeManager);

	glm::ivec3 m_Position;

	std::unique_ptr<engine::gl::VertexArray> m_VertexArray;

	glm::mat4 m_TransformationMatrix;

	std::vector<std::shared_ptr<Chunk>>& m_AllChunksRef;

	std::weak_ptr<Chunk> m_ChunkRef_front;
	std::weak_ptr<Chunk> m_ChunkRef_frontRight;
	std::weak_ptr<Chunk> m_ChunkRef_back;
	std::weak_ptr<Chunk> m_ChunkRef_frontLeft;
	std::weak_ptr<Chunk> m_ChunkRef_top;
	std::weak_ptr<Chunk> m_ChunkRef_bottom;


	std::vector<Node> m_Nodes = std::vector<Node>(CHUNK_VOLUME);
	std::vector<Light> m_LightMap = std::vector<Light>(CHUNK_VOLUME);
};