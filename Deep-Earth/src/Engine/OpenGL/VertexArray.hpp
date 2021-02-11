#pragma once

#include "../Util/TypeDefs.hpp"
#include "../Renderer/Model/Vertex.hpp"
#include <vector>

namespace engine::gl
{
	// Should be implemented within a unique ptr
	class VertexArray
	{
	public:

		VertexArray();
		VertexArray(std::vector<Vertex>& vertices, std::vector<uint>& indices);
		~VertexArray();

		void render();
		void unbind();

		/*
		VertexArray(const VertexArray& other) = default;
		VertexArray(VertexArray&& other) noexcept
			: m_VAO(other.m_VAO), m_VBO(other.m_VBO), m_EBO(other.m_EBO), m_IndicesSize(other.m_IndicesSize)
		{
			other.m_VAO = 0; other.m_VBO = 0; other.m_IndicesSize = 0;
		}
		VertexArray& operator=(const VertexArray& other) = default;
		VertexArray& operator=(VertexArray&& other) noexcept
		{
			if (&other != this)
			{
				m_VAO = other.m_VAO; m_VBO = other.m_VBO; m_EBO = other.m_EBO; m_IndicesSize = other.m_IndicesSize;
				other.m_VAO = 0; other.m_VBO = 0; other.m_EBO = 0; other.m_IndicesSize = 0;
			}

			return *this;
		}
		*/

	private:

		uint m_VAO;
		uint m_VBO;
		uint m_EBO;
		uint m_IndicesSize;
	};
}
