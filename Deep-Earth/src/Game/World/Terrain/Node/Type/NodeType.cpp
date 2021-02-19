#include "NodeType.hpp"

#include "../Texture/NodeTextureManager.hpp"

std::pair<std::vector<engine::NodeVertex>, std::vector<uint>> NodeType::getVerticesWIndices(uint ownID, glm::ivec3& localTransform, uint greatestIndex, bool hide_front, bool hide_frontRight, bool hide_back, bool hide_frontLeft, bool hide_top, bool hide_bottom)
{
	std::vector<uint> tempIndices = m_Indices;

	greatestIndex++;

	for (auto& i : tempIndices)
		i += greatestIndex;

	return std::pair<std::vector<engine::NodeVertex>, std::vector<uint>>(m_Vertices, m_Indices);
}

void NodeType::createMesh()
{
	std::vector<engine::NodeVertex> vertices;

	std::vector vertexPositions = createVertexPositions();
	std::vector uvs = createUVWs();

	vertices.reserve(vertexPositions.size() / 3);

	uint vtxCount = 0;
	uint uvCount = 0;
	for (int i = 0; i < vertexPositions.size() / 3; i++)
	{
		engine::NodeVertex nVertex;
		nVertex.m_Position.x = vertexPositions.at(vtxCount++);
		nVertex.m_Position.y = vertexPositions.at(vtxCount++);
		nVertex.m_Position.z = vertexPositions.at(vtxCount++);

		nVertex.m_UVW.x = uvs.at(uvCount++);
		nVertex.m_UVW.y = uvs.at(uvCount++);
		nVertex.m_UVW.z = uvs.at(uvCount++);

		vertices.emplace_back(nVertex);
	}

	m_Vertices = vertices;
	m_Indices = createIndices();

	createFaces();
}

#include <iostream>

std::vector<float> NodeType::buildUVW(uint top_ID, uint sides_ID, uint bottom_ID)
{
	float top = NodeTextureManager::getWCoord(top_ID);
	float sides = NodeTextureManager::getWCoord(sides_ID);
	float bottom = NodeTextureManager::getWCoord(bottom_ID);

	std::vector<float> uvws =
	{
		0, 0, sides,
		1, 0, sides,
		1, 1, sides,
		0, 1, sides,

		0, 0, sides,
		1, 0, sides,
		1, 1, sides,
		0, 1, sides,

		0, 0, sides,
		1, 0, sides,
		1, 1, sides,
		0, 1, sides,

		0, 0, sides,
		1, 0, sides,
		1, 1, sides,
		0, 1, sides,

		0, 0, top,
		1, 0, top,
		1, 1, top,
		0, 1, top,

		0, 0, bottom,
		1, 0, bottom,
		1, 1, bottom,
		0, 1, bottom
	};

	return uvws;
}

std::vector<float> NodeType::buildUV(int xT, int yT, int xS, int yS, int xB, int yB)
{
	float a = .0625f;
	std::vector<float> uvs =
	{
		0 + (a * xS), 0 + (a * yS),
		.0625f + (a * xS), 0 + (a * yS),
		.0625f + (a * xS), .0625f + (a * yS),
		0 + (a * xS), .0625f + (a * yS),

		0 + (a * xS), 0 + (a * yS),
		.0625f + (a * xS), 0 + (a * yS),
		.0625f + (a * xS), .0625f + (a * yS),
		0 + (a * xS), .0625f + (a * yS),

		0 + (a * xS), 0 + (a * yS),
		.0625f + (a * xS), 0 + (a * yS),
		.0625f + (a * xS), .0625f + (a * yS),
		0 + (a * xS), .0625f + (a * yS),

		0 + (a * xS), 0 + (a * yS),
		.0625f + (a * xS), 0 + (a * yS),
		.0625f + (a * xS), .0625f + (a * yS),
		0 + (a * xS), .0625f + (a * yS),

		0 + (a * xT), 0 + (a * yT),
		.0625f + (a * xT), 0 + (a * yT),
		.0625f + (a * xT), .0625f + (a * yT),
		0 + (a * xT), .0625f + (a * yT),

		0 + (a * xB), 0 + (a * yB),
		.0625f + (a * xB), 0 + (a * yB),
		.0625f + (a * xB), .0625f + (a * yB),
		0 + (a * xB), .0625f + (a * yB)
	};

	return uvs;
}
