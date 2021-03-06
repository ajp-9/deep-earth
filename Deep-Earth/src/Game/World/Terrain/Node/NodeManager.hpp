#pragma once

#include <memory>
#include "Type/NodeType.hpp"
#include "Raw/Node.hpp"
#include "Texture/NodeTextureManager.hpp"

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
	const std::unique_ptr<NodeType>& getNodeType(uint id);
	void bindTextures();

private:

	std::vector<std::unique_ptr<NodeType>> m_NodeTypes;
	NodeTextureManager m_NodeTextureManager;
};
