#pragma once

#include <memory>
#include "Type/BaseBlockType.hpp"
#include "Raw/Node.hpp"

namespace node
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

struct NodeManager
{
	NodeManager();

	Node getNode(uint id);
	const std::unique_ptr<BaseBlockType>& getNodeType(uint id);

private:

	std::vector<std::unique_ptr<BaseBlockType>> m_NodeTypes;
};