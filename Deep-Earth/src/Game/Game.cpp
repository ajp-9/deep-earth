#include "Game.hpp"

#include "World/Terrain/Node/NodeManager.hpp"

#define PROFILE
#include "../Engine/Util/Profile.hpp"

#include "World/Terrain/Light/Light.hpp"

Game::Game()
	: m_Shader("shaders/tex_array/tex_array.vtx.glsl", "shaders/tex_array/tex_array.frg.glsl")
{
	m_Engine.m_Application.setMouseHidden(true);

	m_Shader.bind();

	m_Shader.setProjectionMatrix(glm::perspective(glm::radians(45.0f), float(m_Engine.m_Application.getWindowDimensions().x) / float(m_Engine.m_Application.getWindowDimensions().y), 0.25f, 1000.0f));
}

void Game::run()
{
	while (m_Engine.m_Running)
	{
		m_Shader.bind();
		m_Engine.update();
		m_World.render(m_Shader, m_Engine.m_Application);
	}
}
