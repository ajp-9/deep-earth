#pragma once

#include "Mesh.hpp"
#include "Texture/Texture.hpp"
#include "../../Util/TypeDefs.hpp"

namespace engine
{
	class Model
	{
	public:

		Model();
		Model(Mesh& mesh, Texture& texture);
		Model(std::vector<Vertex>& vertices, std::vector<uint>& indices, const char* path, bool nearest = true);

		void render();

	private:

		Mesh m_Mesh;
		Texture m_Texture;
	};
}
