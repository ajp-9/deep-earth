#include "Chunk.hpp"

#include <algorithm>
#include "../Block/Type/BaseBlockType.hpp"
#include "../../../../Engine/Util/Math.hpp"
#include <iostream>
Chunk::Chunk(BlockManager& blockManager, glm::ivec3 position)
	: m_TransformationMatrix(engine::math::TransMatrix::createTransformationMatrix(position * CHUNK_SIZE))
{
	for (int x = 0; x < CHUNK_VOLUME; x++)
		m_Blocks.at(x) = blockManager.getRawBlock(block::dirt);

	buildMesh(blockManager);
}

Chunk::Chunk(BlockManager& blockManager, std::vector<RawBlock>& m_Blocks, glm::ivec3& position)
	: m_TransformationMatrix(engine::math::TransMatrix::createTransformationMatrix(position * CHUNK_SIZE))
{

}

void Chunk::render(engine::Shader3D& shader)
{
	shader.setModelMatrix(m_TransformationMatrix);
	m_VertexArray->render();
}

void Chunk::buildMesh(BlockManager& blockManager)
{
	std::vector<engine::Vertex> vertices;
	std::vector<uint> indices;

	uint greatestIndex = -1;

	uint indx = -1;
	for (auto& b : m_Blocks)
	{
		++indx;
		if (b.m_ID == block::air)
			continue;
		
		glm::ivec3 bPosition = engine::math::DimensionalAndFlat::get3DFromFlat(indx, CHUNK_SIZE);


		std::vector<engine::Vertex> bVertices = blockManager.getBlockType(b.m_ID)->getVertices(bPosition); // you have to transform by sending the coords thru getVtx
		std::vector<uint> bIndices = blockManager.getBlockType(b.m_ID)->getIndices(greatestIndex);

		vertices.insert(vertices.end(), bVertices.begin(), bVertices.end());
		indices.insert(indices.end(), bIndices.begin(), bIndices.end());

		greatestIndex = *std::max_element(bIndices.begin(), bIndices.end());
	}

	m_VertexArray = std::make_unique<engine::gl::VertexArray>(vertices, indices);
}
