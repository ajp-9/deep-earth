#pragma once

#include "BlockType.hpp"

struct SandType : public BlockType
{
	SandType() { createMesh(); }

private:

	virtual std::vector<float> createUVs() override
	{
		return buildUV(0, 14, 0, 14, 0, 14);
	}
};