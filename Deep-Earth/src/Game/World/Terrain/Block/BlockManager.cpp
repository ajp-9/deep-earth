#include "BlockManager.hpp"

#include "Type/Block/AirType.hpp"
#include "Type/Block/GrassType.hpp"
#include "Type/Block/DirtType.hpp"
#include "Type/Block/SandType.hpp"

BlockManager::BlockManager()
{
	m_BlockTypes.emplace_back(std::make_unique<AirType>());
	m_BlockTypes.emplace_back(std::make_unique<GrassType>());
	m_BlockTypes.emplace_back(std::make_unique<DirtType>());
	m_BlockTypes.emplace_back(std::make_unique<SandType>());
}

RawBlock BlockManager::getRawBlock(uint id)
{
	return RawBlock(id);
}

const std::unique_ptr<BaseBlockType>& BlockManager::getBlockType(uint id)
{
	return m_BlockTypes.at(id);
}
