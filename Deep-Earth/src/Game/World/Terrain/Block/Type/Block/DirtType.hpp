#pragma once

#include "BlockType.hpp"

struct DirtType : public BlockType
{
	DirtType() { createMesh(); }

private:

	virtual std::vector<float> createUVs() override
	{
		return buildUV(2, 15, 2, 15, 2, 15);
	}
};