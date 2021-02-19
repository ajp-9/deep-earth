#pragma once

#include <vector>
#include "../../../../../Engine/Renderer/Model/Vertex.hpp"
#include "../../../../../Engine/Util/TypeDefs.hpp"

struct NodeType
{
	// Get vertices with indices.
	virtual std::pair<std::vector<engine::Vertex>, std::vector<uint>> getVerticesWIndices(uint ownID, glm::ivec3& localTransform, uint greatestIndex, bool hide_front, bool hide_frontRight, bool hide_back, bool hide_frontLeft, bool hide_top, bool hide_bottom);
	
	bool doesOcclude = true;

protected:

	void createMesh();
	
	virtual std::vector<float> createVertexPositions() = 0;
	virtual std::vector<uint> createIndices() = 0;
	virtual std::vector<float> createUVs() = 0;
	virtual void createFaces() = 0;

	std::vector<float> buildUV(int xT, int yT, int xS, int yS, int xB, int yB);

	bool customMesh = false;

	std::vector<engine::Vertex> m_Vertices;
	std::vector<uint> m_Indices;
};