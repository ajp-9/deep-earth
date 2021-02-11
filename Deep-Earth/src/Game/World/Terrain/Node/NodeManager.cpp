#include "NodeManager.hpp"

#include "Type/Block/AirType.hpp"
#include "Type/Block/GrassType.hpp"
#include "Type/Block/DirtType.hpp"
#include "Type/Block/SandType.hpp"

NodeManager::NodeManager()
{
	m_NodeTypes.emplace_back(std::make_unique<AirType>());
	m_NodeTypes.emplace_back(std::make_unique<GrassType>());
	m_NodeTypes.emplace_back(std::make_unique<DirtType>());
	m_NodeTypes.emplace_back(std::make_unique<SandType>());
}

Node NodeManager::getNode(uint id)
{
	return Node(id);
}

const std::unique_ptr<BaseBlockType>& NodeManager::getNodeType(uint id)
{
	return m_NodeTypes.at(id);
}
