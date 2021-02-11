#include "Mesh.hpp"

#include <glad/glad.h>

namespace engine
{
	Mesh::Mesh() {}

	Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<uint>& indices)
		: m_VertexArray(std::make_unique<gl::VertexArray>(vertices, indices)), m_Vertices(vertices), m_Indices(indices)
	{}

	void Mesh::render()
	{
		m_VertexArray->render();
	}
}
