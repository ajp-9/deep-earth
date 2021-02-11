#pragma once

#include <vector>
#include <memory>
#include "Vertex.hpp"
#include "../../Util/TypeDefs.hpp"
#include "../../OpenGL/VertexArray.hpp"

namespace engine
{
	class Mesh
	{
	public:

		Mesh();
		Mesh(std::vector<Vertex>& vertices, std::vector<uint>& indices);

		void render();

	private:

		std::unique_ptr<gl::VertexArray> m_VertexArray;
		std::vector<Vertex> m_Vertices;
		std::vector<uint> m_Indices;
	};
}
