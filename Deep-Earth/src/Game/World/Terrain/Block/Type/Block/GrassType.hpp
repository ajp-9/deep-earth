#pragma once

#include "BlockType.hpp"

struct GrassType : public BlockType
{
	GrassType() { createMesh(); }

private:

	virtual std::vector<float> createUVs() override
	{
		return buildUV(0, 15, 1, 15, 2, 15);
	}
};