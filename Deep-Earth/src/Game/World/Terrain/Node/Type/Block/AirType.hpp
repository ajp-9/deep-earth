#pragma once

#include "BlockType.hpp"

struct AirType : public BlockType
{
	AirType()
	{
		doesOcclude = false;
	}

private:

	virtual std::vector<float> createUVWs() override
	{
		return std::vector<float>(0);
	}
};
