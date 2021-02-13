#pragma once

#include <array>
#include "../BaseBlockType.hpp"

struct BlockType : public BaseBlockType
{
	virtual std::pair<std::vector<engine::Vertex>, std::vector<uint>> getVerticesWIndices(uint ownID, glm::ivec3& localTransform, uint greatestIndex, bool hide_front, bool hide_frontRight, bool hide_back, bool hide_frontLeft, bool hide_top, bool hide_bottom) override;

    virtual std::vector<engine::Vertex> getVertices(glm::ivec3 localTransform, bool front = true, bool frontRight = true, bool back = true, bool frontLeft = true, bool top = true, bool bottom = true) override;
    virtual std::vector<uint> getIndices(uint greatestIndex, bool front = true, bool frontRight = true, bool back = true, bool frontLeft = true, bool top = true, bool bottom = true) override;

protected:

    virtual std::vector<float> createVertexPositions() override;
    virtual std::vector<uint> createIndices() override;
    virtual std::vector<float> createUVs() = 0;

    virtual void createFaces() override;

	std::vector<engine::Vertex> m_VerticesFrontFace;
	std::vector<engine::Vertex> m_VerticesFrontRightFace;
	std::vector<engine::Vertex> m_VerticesBackFace;
	std::vector<engine::Vertex> m_VerticesFrontLeftFace;
	std::vector<engine::Vertex> m_VerticesTopFace;
	std::vector<engine::Vertex> m_VerticesBottomFace;

	std::vector<uint> m_IndicesFace;
};