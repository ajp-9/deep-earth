#include "Model.hpp"

namespace engine
{
	Model::Model() {}
	// watch out -- this is the problem ch..-function! LOL!
	Model::Model(Mesh& mesh, Texture& texture)
		: m_Mesh(std::move(mesh)), m_Texture(texture)
	{}
	Model::Model(std::vector<Vertex>& vertices, std::vector<uint>& indices, const char* path, bool nearest)
		: m_Mesh(Mesh(vertices, indices)), m_Texture(Texture(path, nearest))
	{}
	
	void Model::render()
	{
		m_Texture.bind();
		m_Mesh.render();
	}
}
