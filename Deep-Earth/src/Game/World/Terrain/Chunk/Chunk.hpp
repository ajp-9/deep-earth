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

	Chunk(NodeManager& nodeManager, glm::ivec3 position);
	Chunk(NodeManager& nodeManager, std::vector<Node>& m_Blocks, glm::ivec3& position);

	void render(engine::Shader3D& shader);

	Node getNode(glm::ivec3 position);
	void setNode(glm::ivec3 position, uint id);

private:

	void buildMesh(NodeManager& nodeManager);

	std::unique_ptr<engine::gl::VertexArray> m_VertexArray;

	glm::mat4 m_TransformationMatrix;

	std::vector<Node> m_Nodes = std::vector<Node>(CHUNK_VOLUME);
	std::vector<Light> m_LightMap = std::vector<Light>(CHUNK_VOLUME);
};