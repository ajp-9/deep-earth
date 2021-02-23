#include "World.hpp"

World::World()
	: m_Player(glm::vec3(0, 0, 0))
{}

World::~World()
{
}

void World::render(engine::Shader3D& shader)
{
	shader.setViewMatrix(m_Player.getViewMatrix());
	m_Terrain.render(shader);

	//for (auto& e : m_Registry.view<Renderable>())
	//	m_Registry.get<Renderable>(e).render;
}

void World::update(engine::Application& app)
{
	m_Terrain.update(m_Player.getPosition());
	m_Player.update(app, m_Terrain.getChunkManager());
}
