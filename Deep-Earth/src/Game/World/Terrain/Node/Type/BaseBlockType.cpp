#include "BaseBlockType.hpp"

std::pair<std::vector<engine::Vertex>, std::vector<uint>> BaseBlockType::getVerticesWIndices(uint ownID, glm::ivec3& localTransform, uint greatestIndex, bool hide_front, bool hide_frontRight, bool hide_back, bool hide_frontLeft, bool hide_top, bool hide_bottom)
{
	std::vector<uint> tempIndices = m_Indices;

	greatestIndex++;

	for (auto& i : tempIndices)
		i += greatestIndex;

	return std::pair<std::vector<engine::Vertex>, std::vector<uint>>(m_Vertices, m_Indices);
}

void BaseBlockType::createMesh()
{
	std::vector<engine::Vertex> vertices;

	std::vector vertexPositions = createVertexPositions();
	std::vector uvs = createUVs();

	vertices.reserve(vertexPositions.size() / 3);

	uint vtxCount = 0;
	uint uvCount = 0;
	for (int i = 0; i < vertexPositions.size() / 3; i++)
	{
		engine::Vertex vertex;
		vertex.m_Position.x = vertexPositions.at(vtxCount++);
		vertex.m_Position.y = vertexPositions.at(vtxCount++);
		vertex.m_Position.z = vertexPositions.at(vtxCount++);

		vertex.m_UV.x = uvs.at(uvCount++);
		vertex.m_UV.y = uvs.at(uvCount++);

		vertices.emplace_back(vertex);
	}

	m_Vertices = vertices;
	m_Indices = createIndices();

	createFaces();
}

std::vector<float> BaseBlockType::buildUV(int xT, int yT, int xS, int yS, int xB, int yB)
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