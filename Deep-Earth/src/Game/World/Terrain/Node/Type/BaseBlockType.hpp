#pragma once

#include <vector>
#include "../../../../../Engine/Renderer/Model/Vertex.hpp"
#include "../../../../../Engine/Util/TypeDefs.hpp"

struct BaseBlockType
{
	// Get vertices with indices.
	virtual std::pair<std::vector<engine::Vertex>, std::vector<uint>> getVerticesWIndices(uint ownID, glm::ivec3& localTransform, uint greatestIndex, bool hide_front, bool hide_frontRight, bool hide_back, bool hide_frontLeft, bool hide_top, bool hide_bottom);
	
	virtual std::vector<engine::Vertex> getVertices(glm::ivec3 localTransform, bool front = true, bool frontRight = true, bool back = true, bool frontLeft = true, bool top = true, bool bottom = true);
	virtual std::vector<uint> getIndices(uint greatestIndex, bool front = true, bool frontRight = true, bool back = true, bool frontLeft = true, bool top = true, bool bottom = true);

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