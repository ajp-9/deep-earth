#pragma once

#include "../Block/Raw/RawBlock.hpp"
#include "../Light/Light.hpp"
#include "../../../../Engine/OpenGL/VertexArray.hpp"
#include "../../../../Engine/Renderer/Shader/Shader3D.hpp"
#include "../Block/BlockManager.hpp"
#include "../../../../Engine/Util/Math.hpp"
#include <iostream>

#define CHUNK_SIZE 32
#define CHUNK_VOLUME 32768 // 32*32*32

class Chunk
{
public:

	Chunk(BlockManager& blockManager, glm::ivec3 position);
	Chunk(BlockManager& blockManager, std::vector<RawBlock>& m_Blocks, glm::ivec3& position);

	void render(engine::Shader3D& shader);

	RawBlock& getBlock(glm::ivec3 position);
	void setBlock(glm::ivec3 position, uint id);

private:

	void buildMesh(BlockManager& blockManager);

	std::unique_ptr<engine::gl::VertexArray> m_VertexArray;

	glm::mat4 m_TransformationMatrix;

	std::vector<RawBlock> m_Blocks = std::vector<RawBlock>(CHUNK_VOLUME);
	std::vector<Light> m_LightMap = std::vector<Light>(CHUNK_VOLUME);
};