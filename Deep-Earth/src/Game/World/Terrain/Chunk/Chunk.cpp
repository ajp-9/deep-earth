#include "Chunk.hpp"

#include <algorithm>
#include "../Node/Type/BaseBlockType.hpp"

#define PROFILE
#include "../../../../Engine/Util/Profile.hpp"

#include "ChunkDatabase.hpp"

Chunk::Chunk(NodeManager& nodeManager, glm::ivec3 position, ChunkDatabase& chunkDatabase)
	: m_Position(position), m_TransformationMatrix(engine::math::TransMatrix::createTransformationMatrix(position * CHUNK_SIZE)), m_ChunkDatabase(chunkDatabase)
{
	for (int x = 0; x < CHUNK_VOLUME; x++)
		m_Nodes.at(x) = nodeManager.getNode(node::grass);

	//buildMesh(nodeManager);
}

Chunk::Chunk(NodeManager& nodeManager, std::vector<Node>& m_Nodes, glm::ivec3& position, ChunkDatabase& chunkDatabase)
	: m_Position(position), m_TransformationMatrix(engine::math::TransMatrix::createTransformationMatrix(position * CHUNK_SIZE)), m_ChunkDatabase(chunkDatabase)
{

}

void Chunk::render(engine::Shader3D& shader)
{
	if (m_VertexArray != nullptr)
	{
		shader.setModelMatrix(m_TransformationMatrix);
		m_VertexArray->render();
	}
}

void Chunk::tick()
{
}

inline Node& Chunk::getNode(glm::ivec3 position)
{
	if (position.x >= CHUNK_SIZE || position.x < 0
	||  position.y >= CHUNK_SIZE || position.y < 0
	||  position.z >= CHUNK_SIZE || position.z < 0)
	{
		Node node = Node(node::air);
		return node;
	}
	else
	{
		uint flat = engine::math::DimensionalAndFlat::getFlatFrom3D(position, CHUNK_SIZE);
		return m_Nodes.at(flat);
	}
}

inline void Chunk::setNode(glm::ivec3 position, uint id)
{
	uint flat = engine::math::DimensionalAndFlat::getFlatFrom3D(position, CHUNK_SIZE);

	if (flat >= CHUNK_VOLUME || flat < 0)
	{
		std::cout << "ERROR::<Chunk::setNode>: Out of bounds exception!\n";
	}
	else
	{
		m_Nodes.at(flat) = Node(id);
	}
}

void Chunk::getNeighboringChunks()
{
	if (m_ChunkRef_front.expired())
		m_ChunkDatabase.getChunkWCallback(glm::ivec3(m_Position.x, m_Position.y - 1, m_Position.z), m_ChunkRef_front);

	if (m_ChunkRef_frontRight.expired())
		m_ChunkDatabase.getChunkWCallback(glm::ivec3(m_Position.x + 1, m_Position.y, m_Position.z), m_ChunkRef_frontRight);

	if (m_ChunkRef_back.expired())
		m_ChunkDatabase.getChunkWCallback(glm::ivec3(m_Position.x, m_Position.y + 1, m_Position.z), m_ChunkRef_back);

	if (m_ChunkRef_frontLeft.expired())
		m_ChunkDatabase.getChunkWCallback(glm::ivec3(m_Position.x - 1, m_Position.y, m_Position.z), m_ChunkRef_frontLeft);

	if (m_ChunkRef_top.expired())
		m_ChunkDatabase.getChunkWCallback(glm::ivec3(m_Position.x, m_Position.y, m_Position.z + 1), m_ChunkRef_top);

	if (m_ChunkRef_bottom.expired())
		m_ChunkDatabase.getChunkWCallback(glm::ivec3(m_Position.x, m_Position.y, m_Position.z - 1), m_ChunkRef_bottom);
}

void Chunk::buildMesh(NodeManager& nodeManager)
{
	getNeighboringChunks();

	std::vector<engine::Vertex> vertices;
	std::vector<uint> indices;

	uint indx = -1;
	uint greatestIndex = -1;
	{
		for (auto& b : m_Nodes)
		{
			++indx;
			if (b.m_ID == node::air)
				continue;

			glm::ivec3 bPosition = engine::math::DimensionalAndFlat::get3DFromFlat(indx, CHUNK_SIZE);

			// Does node occlude the side.
			bool doesFrontOcclude, doesFrontRightOcclude, doesBackOcclude, doesFrontLeftOcclude, doesTopOcclude, doesBottomOcclude;

			// front
			if (bPosition.y)
			{
				doesFrontOcclude = nodeManager.getNodeType(getNode(glm::ivec3(bPosition.x, CHUNK_SIZE - 1, bPosition.z)).m_ID)->doesOcclude;
			}
			else
			{
				if (!m_ChunkRef_front.expired())
					doesFrontOcclude = nodeManager.getNodeType(m_ChunkRef_front.lock()->getNode(glm::ivec3(bPosition.x, CHUNK_SIZE - 1, bPosition.z)).m_ID)->doesOcclude;
				else
					doesFrontOcclude = false;
			}

			// front right
			if (bPosition.x != CHUNK_SIZE - 1)
			{
				doesFrontRightOcclude = nodeManager.getNodeType(getNode(glm::ivec3(bPosition.x + 1, bPosition.y, bPosition.z)).m_ID)->doesOcclude;
			}
			else
			{
				if (!m_ChunkRef_frontRight.expired())
					doesFrontRightOcclude = nodeManager.getNodeType(m_ChunkRef_frontRight.lock()->getNode(glm::ivec3(0, bPosition.y, bPosition.z)).m_ID)->doesOcclude;
				else
					doesFrontRightOcclude = false;
			}

			// back
			if (bPosition.y != CHUNK_SIZE - 1)
			{
				doesBackOcclude = nodeManager.getNodeType(getNode(glm::ivec3(bPosition.x, 0, bPosition.z)).m_ID)->doesOcclude;
			}
			else
			{
				if (!m_ChunkRef_back.expired())
					doesBackOcclude = nodeManager.getNodeType(m_ChunkRef_back.lock()->getNode(glm::ivec3(bPosition.x, 0, bPosition.z)).m_ID)->doesOcclude;
				else
					doesBackOcclude = false;
			}

			// front left
			if (bPosition.x)
			{
				doesFrontLeftOcclude = nodeManager.getNodeType(getNode(glm::ivec3(CHUNK_SIZE - 1, bPosition.y, bPosition.z)).m_ID)->doesOcclude;
			}
			else
			{
				if (!m_ChunkRef_frontLeft.expired())
					doesFrontLeftOcclude = nodeManager.getNodeType(m_ChunkRef_frontLeft.lock()->getNode(glm::ivec3(CHUNK_SIZE - 1, bPosition.y, bPosition.z)).m_ID)->doesOcclude;
				else
					doesFrontLeftOcclude = false;
			}

			// top
			if (bPosition.z != CHUNK_SIZE - 1)
			{
				doesTopOcclude = nodeManager.getNodeType(getNode(glm::ivec3(bPosition.x, bPosition.y, 0)).m_ID)->doesOcclude;
			}
			else
			{
				if (!m_ChunkRef_top.expired())
					doesTopOcclude = nodeManager.getNodeType(m_ChunkRef_top.lock()->getNode(glm::ivec3(bPosition.x, bPosition.y, 0)).m_ID)->doesOcclude;
				else
					doesTopOcclude = false;
			}

			// bottom
			if (bPosition.z)
			{
				doesBottomOcclude = nodeManager.getNodeType(getNode(glm::ivec3(bPosition.x, bPosition.y, CHUNK_SIZE - 1)).m_ID)->doesOcclude;
			}
			else
			{
				if (!m_ChunkRef_bottom.expired())
					doesBottomOcclude = nodeManager.getNodeType(m_ChunkRef_bottom.lock()->getNode(glm::ivec3(bPosition.x, bPosition.y, CHUNK_SIZE - 1)).m_ID)->doesOcclude;
				else
					doesBottomOcclude = false;
			}

			std::pair<std::vector<engine::Vertex>, std::vector<uint>> bVerticesWIndices = nodeManager.getNodeType(b.m_ID)->getVerticesWIndices(b.m_ID, bPosition, greatestIndex,
				doesFrontOcclude, doesFrontRightOcclude,
				doesBackOcclude, doesFrontLeftOcclude,
				doesTopOcclude, doesBottomOcclude);

			if (!bVerticesWIndices.first.size() || !bVerticesWIndices.second.size())
				continue;

			vertices.insert(vertices.end(), bVerticesWIndices.first.begin(), bVerticesWIndices.first.end());
			indices.insert(indices.end(), bVerticesWIndices.second.begin(), bVerticesWIndices.second.end());

			greatestIndex = *std::max_element(bVerticesWIndices.second.begin(), bVerticesWIndices.second.end()); // optimize this
		}
	}

	if(vertices.size() && indices.size())
		m_VertexArray = std::make_unique<engine::gl::VertexArray>(vertices, indices);
}

//std::cout << m_Position.x << ", " << m_Position.y << ", " << m_Position.z << "\n";
