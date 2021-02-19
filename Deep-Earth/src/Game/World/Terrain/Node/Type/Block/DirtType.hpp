#pragma once

#include "BlockType.hpp"

struct DirtType : public BlockType
{
	DirtType() { createMesh(); }

private:

	virtual std::vector<float> createUVWs() override
	{
		return buildUVW(node::texture::dirt, node::texture::dirt, node::texture::dirt);
	}
};