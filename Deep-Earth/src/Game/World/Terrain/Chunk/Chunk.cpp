#include "Chunk.hpp"

#include <algorithm>
#include "../Node/Type/BaseBlockType.hpp"

#define PROFILE
#include "../../../../Engine/Util/Profile.hpp"

Chunk::Chunk(NodeManager& nodeManager, glm::ivec3 position)
	: m_TransformationMatrix(engine::math::TransMatrix::createTransformationMatrix(position * CHUNK_SIZE))
{
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

inline Node Chunk::getNode(glm::ivec3 position)
{
	uint flat = engine::math::DimensionalAndFlat::getFlatFrom3D(position, CHUNK_SIZE);

	if (position.x >= CHUNK_SIZE || position.x < 0
	||  position.y >= CHUNK_SIZE || position.y < 0
	||  position.z >= CHUNK_SIZE || position.z < 0)
	{
		return Node(node::air);
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

		std::pair<std::vector<engine::Vertex>, std::vector<uint>> bVerticesWIndices = nodeManager.getNodeType(b.m_ID)->getVerticesWIndices(b.m_ID, bPosition, greatestIndex,
			nodeManager.getNodeType(getNode(glm::ivec3(bPosition.x, bPosition.y - 1, bPosition.z)).m_ID)->doesOcclude,
			nodeManager.getNodeType(getNode(glm::ivec3(bPosition.x + 1, bPosition.y, bPosition.z)).m_ID)->doesOcclude,
			nodeManager.getNodeType(getNode(glm::ivec3(bPosition.x, bPosition.y + 1, bPosition.z)).m_ID)->doesOcclude,
			nodeManager.getNodeType(getNode(glm::ivec3(bPosition.x - 1, bPosition.y, bPosition.z)).m_ID)->doesOcclude,
			nodeManager.getNodeType(getNode(glm::ivec3(bPosition.x, bPosition.y, bPosition.z + 1)).m_ID)->doesOcclude,
			nodeManager.getNodeType(getNode(glm::ivec3(bPosition.x, bPosition.y, bPosition.z - 1)).m_ID)->doesOcclude);

		if (!bVerticesWIndices.first.size() || !bVerticesWIndices.second.size())
			continue;

		vertices.insert(vertices.end(), bVerticesWIndices.first.begin(), bVerticesWIndices.first.end());
		indices.insert(indices.end(), bVerticesWIndices.second.begin(), bVerticesWIndices.second.end());

		greatestIndex = *std::max_element(bVerticesWIndices.second.begin(), bVerticesWIndices.second.end()); // optimize this
	}

	if(vertices.size() && indices.size())
		m_VertexArray = std::make_unique<engine::gl::VertexArray>(vertices, indices);
}
