#include "NodeTextureManager.hpp"

NodeTextureManager::NodeTextureManager()
{
	m_TextureArray.addTexture("res/node_textures/0-grass/grass.png");
	m_TextureArray.addTexture("res/node_textures/1-grass_side/grass_side.png");
	m_TextureArray.addTexture("res/node_textures/2-dirt/dirt.png");
	m_TextureArray.addTexture("res/node_textures/3-sand/sand.png");
}

float NodeTextureManager::getWCoord(byte tex_id)
{
	return tex_id;
}

void NodeTextureManager::bind()
{
	m_TextureArray.bind();
}
