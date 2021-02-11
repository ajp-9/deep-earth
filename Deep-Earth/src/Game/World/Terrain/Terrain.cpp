#include "Terrain.hpp"

Terrain::Terrain()
	: m_ChunkManager(m_BlockManager), m_Atlas("res/textures/atlas.png")
{}

void Terrain::render(engine::Shader3D& shader)
{
	m_Atlas.bind();
	m_ChunkManager.render(shader);
}

void Terrain::update()
{
}