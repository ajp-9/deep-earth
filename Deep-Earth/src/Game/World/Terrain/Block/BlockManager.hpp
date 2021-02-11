#pragma once

#include <memory>
#include "Type/BaseBlockType.hpp"
#include "Raw/RawBlock.hpp"

namespace block
{
	enum
	{
		air,
		grass,
		dirt,
		sand,
		stone
	};
}

struct BlockManager
{
	BlockManager();

	RawBlock getRawBlock(uint id);
	const std::unique_ptr<BaseBlockType>& getBlockType(uint id);

private:

	std::vector<std::unique_ptr<BaseBlockType>> m_BlockTypes;
};