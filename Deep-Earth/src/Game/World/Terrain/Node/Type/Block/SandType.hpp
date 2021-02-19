#pragma once

#include "BlockType.hpp"

struct SandType : public BlockType
{
	SandType() { createMesh(); }

private:

	virtual std::vector<float> createUVWs() override
	{
		return buildUVW(node::texture::sand, node::texture::sand, node::texture::sand);
	}
};