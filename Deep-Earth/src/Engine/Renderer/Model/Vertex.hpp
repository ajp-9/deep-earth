#pragma once

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

namespace engine
{
	struct Vertex
	{
		Vertex()
			: m_Position(0), m_UV(0)
		{}

		Vertex(glm::vec3 position, glm::vec2 uv)
			: m_Position(position), m_UV(uv)
		{}
		
		glm::vec3 m_Position;
		glm::vec2 m_UV;
	};

	struct NodeVertex
	{
		NodeVertex()
			: m_Position(0), m_UVW(0)
		{}

		NodeVertex(glm::vec3 position, glm::vec3 uvw)
			: m_Position(position), m_UVW(uvw)
		{}

		glm::vec3 m_Position;
		glm::vec3 m_UVW;
	};
}
