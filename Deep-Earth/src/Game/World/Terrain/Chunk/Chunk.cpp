#include "Chunk.hpp"

#include <algorithm>
#include "../Node/Type/BaseBlockType.hpp"

Chunk::Chunk(NodeManager& nodeManager, glm::ivec3 position)
	: m_TransformationMatrix(engine::math::TransMatrix::createTransformationMatrix(position * CHUNK_SIZE))
{
	//setNode(glm::ivec3(0), node::sand);
	for (int x = 0; x < CHUNK_VOLUME; x++)
		m_Nodes.at(x) = nodeManager.getNode(node::grass);

	buildMesh(nodeManager);
}

Chunk::Chunk(NodeManager& nodeManager, std::vector<Node>& m_Nodes, glm::ivec3& position)
	: m_TransformationMatrix(engine::math::TransMatrix::createTransformationMatrix(position * CHUNK_SIZE))
{

}

void Chunk::render(engine::Shader3D& shader)
{
	shader.setModelMatrix(m_TransformationMatrix);
	m_VertexArray->render();
}

inline Node& Chunk::getNode(glm::ivec3 position)
{
	uint flat = engine::math::DimensionalAndFlat::getFlatFrom3D(position, CHUNK_SIZE);

	if (flat >= CHUNK_VOLUME || flat < 0)
	{
		std::cout << "ERROR::<Chunk::getNode> Out of bounds exception!\n";
	}
	else
	{
		return m_Nodes.at(flat);
	}
}

inline void Chunk::setNode(glm::ivec3 position, uint id)
{
	uint flat = engine::math::DimensionalAndFlat::getFlatFrom3D(position, CHUNK_SIZE);

	if (flat >= CHUNK_VOLUME || flat < 0)
	{
		std::cout << "ERROR::<Chunk::setNode> Out of bounds exception!\n";
	}
	else
	{
		m_Nodes.at(flat) = Node(id);
	}
}

void Chunk::buildMesh(NodeManager& nodeManager)
{
	std::vector<engine::Vertex> vertices;
	std::vector<uint> indices;

	uint indx = -1;
	uint greatestIndex = -1;
	for (auto& b : m_Nodes)
	{
		++indx;
		if (b.m_ID == node::air)
			continue;
		
		glm::ivec3 bPosition = engine::math::DimensionalAndFlat::get3DFromFlat(indx, CHUNK_SIZE);

		// front
		// front-right
		// back
		// front-left
		// top
		// bottom

		//std::cout << engine::math::DimensionalAndFlat::getFlatFrom3D(glm::ivec3(31, 31, 31), 32) << std::endl;
		//std::cout << engine::math::DimensionalAndFlat::get3DFromFlat(32767, 32).x << ", " << engine::math::DimensionalAndFlat::get3DFromFlat(32767, 32).y << ", " << engine::math::DimensionalAndFlat::get3DFromFlat(32767, 32).z << std::endl;

		std::vector<engine::Vertex> bVertices = nodeManager.getNodeType(b.m_ID)->getVertices(bPosition);
		std::vector<uint> bIndices = nodeManager.getNodeType(b.m_ID)->getIndices(greatestIndex);

		vertices.insert(vertices.end(), bVertices.begin(), bVertices.end());
		indices.insert(indices.end(), bIndices.begin(), bIndices.end());

		greatestIndex = *std::max_element(bIndices.begin(), bIndices.end()); // optimize this
	}

	m_VertexArray = std::make_unique<engine::gl::VertexArray>(vertices, indices);
}
