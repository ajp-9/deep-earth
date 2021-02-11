#pragma once

#include <vector>
#include "../../../../../Engine/Renderer/Model/Vertex.hpp"
#include "../../../../../Engine/Util/TypeDefs.hpp"

struct BaseBlockType
{
	virtual std::vector<engine::Vertex> getVertices(glm::ivec3 localTransform, bool front = true, bool frontRight = true, bool back = true, bool frontLeft = true, bool top = true, bool bottom = true);
	virtual std::vector<uint> getIndices(uint greatestIndex, bool front = true, bool frontRight = true, bool back = true, bool frontLeft = true, bool top = true, bool bottom = true);

	bool customMesh = false;

protected:

	void createMesh();
	
	virtual std::vector<float> createVertexPositions() = 0;
	virtual std::vector<uint> createIndices() = 0;
	virtual std::vector<float> createUVs() = 0;
	virtual void createFaces() = 0;

	std::vector<float> buildUV(int xT, int yT, int xS, int yS, int xB, int yB);

	std::vector<engine::Vertex> m_Vertices;
	std::vector<uint> m_Indices;
};