#pragma once

#include "BlockType.hpp"

struct AirType : public BlockType
{
	AirType()
	{
		doesOcclude = false;
	}

private:

	virtual std::vector<float> createUVs() override
	{
		return std::vector<float>(0);
	}
};
