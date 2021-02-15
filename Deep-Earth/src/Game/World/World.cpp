#include "World.hpp"

World::World()
	: m_Player(glm::vec3(0, 0, 0))
{}

World::~World()
{
}

void World::render(engine::Shader3D& shader, engine::Application& app)
{
	shader.setViewMatrix(m_Player.getViewMatrix());
	m_Terrain.render(shader, m_Player.getPosition());
	m_Player.update(app);

	//for (auto& e : m_Registry.view<Renderable>())
	//	m_Registry.get<Renderable>(e).render;
}
