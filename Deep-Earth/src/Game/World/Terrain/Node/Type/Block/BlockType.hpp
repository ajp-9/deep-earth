#pragma once

#include <array>
#include "../NodeType.hpp"

struct BlockType : public NodeType
{
	virtual std::pair<std::vector<engine::NodeVertex>, std::vector<uint>> getVerticesWIndices(uint ownID, glm::ivec3& localTransform, uint greatestIndex, bool hide_front, bool hide_frontRight, bool hide_back, bool hide_frontLeft, bool hide_top, bool hide_bottom) override;

protected:

    virtual std::vector<float> createVertexPositions() override;
    virtual std::vector<uint> createIndices() override;
    //virtual std::vector<float> createUVs() = 0;

    virtual void createFaces() override;

	std::vector<engine::NodeVertex> m_VerticesFrontFace;
	std::vector<engine::NodeVertex> m_VerticesFrontRightFace;
	std::vector<engine::NodeVertex> m_VerticesBackFace;
	std::vector<engine::NodeVertex> m_VerticesFrontLeftFace;
	std::vector<engine::NodeVertex> m_VerticesTopFace;
	std::vector<engine::NodeVertex> m_VerticesBottomFace;

	std::vector<uint> m_IndicesFace;
};