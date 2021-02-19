#pragma once

#include "BlockType.hpp"

struct GrassType : public BlockType
{
	GrassType() { createMesh(); }

private:

	virtual std::vector<float> createUVWs() override
	{
		return buildUVW(node::texture::grass, node::texture::grass_side, node::texture::dirt);
	}
};
