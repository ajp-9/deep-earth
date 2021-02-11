#include "Chunk.hpp"

#include <algorithm>
#include "../Block/Type/BaseBlockType.hpp"
#include <iostream>
Chunk::Chunk(BlockManager& blockManager, glm::ivec3 position)
	: m_TransformationMatrix(engine::math::TransMatrix::createTransformationMatrix(position * CHUNK_SIZE))
{
	setBlock(glm::ivec3(0), block::sand);
	//for (int x = 0; x < CHUNK_VOLUME; x++)
	//	m_Blocks.at(x) = blockManager.getRawBlock(block::dirt);

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

inline RawBlock& Chunk::getBlock(glm::ivec3 position)
{
	uint flat = engine::math::DimensionalAndFlat::getFlatFrom3D(position, CHUNK_SIZE);

	if (flat >= CHUNK_VOLUME || flat < 0)
	{
		std::cout << "ERROR::<Chunk::getBlock> Out of bounds exception!\n";
	}
	else
	{
		return m_Blocks.at(flat);
	}
}

inline void Chunk::setBlock(glm::ivec3 position, uint id)
{
	uint flat = engine::math::DimensionalAndFlat::getFlatFrom3D(position, CHUNK_SIZE);

	if (flat >= CHUNK_VOLUME || flat < 0)
	{
		std::cout << "ERROR::<Chunk::getBlock> Out of bounds exception!\n";
	}
	else
	{
		m_Blocks.at(flat) = RawBlock(id);
	}
}

void Chunk::buildMesh(BlockManager& blockManager)
{
	std::vector<engine::Vertex> vertices;
	std::vector<uint> indices;

	uint indx = -1;
	uint greatestIndex = -1;
	for (auto& b : m_Blocks)
	{
		++indx;
		if (b.m_ID == block::air)
			continue;
		
		glm::ivec3 bPosition = engine::math::DimensionalAndFlat::get3DFromFlat(indx, CHUNK_SIZE);

		// front
		//if()
		// front-right
		// back
		// front-left
		// top
		// bottom

		//std::cout << engine::math::DimensionalAndFlat::getFlatFrom3D(glm::ivec3(31, 31, 31), 32) << std::endl;
		//std::cout << engine::math::DimensionalAndFlat::get3DFromFlat(32767, 32).x << ", " << engine::math::DimensionalAndFlat::get3DFromFlat(32767, 32).y << ", " << engine::math::DimensionalAndFlat::get3DFromFlat(32767, 32).z << std::endl;

		std::vector<engine::Vertex> bVertices = blockManager.getBlockType(b.m_ID)->getVertices(bPosition); // you have to transform by sending the coords thru getVtx
		std::vector<uint> bIndices = blockManager.getBlockType(b.m_ID)->getIndices(greatestIndex);

		vertices.insert(vertices.end(), bVertices.begin(), bVertices.end());
		indices.insert(indices.end(), bIndices.begin(), bIndices.end());

		greatestIndex = *std::max_element(bIndices.begin(), bIndices.end()); // optimize this
	}

	m_VertexArray = std::make_unique<engine::gl::VertexArray>(vertices, indices);
}
