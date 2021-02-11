#include "Game.hpp"

#include "World/Terrain/Block/BlockManager.hpp"
#include "World/Terrain/Block/Type/Block/GrassType.hpp"

#define PROFILE
#include "../Engine/Util/Profile.hpp"

#include "World/Terrain/Light/Light.hpp"

Game::Game()
	: m_Shader("res/shaders/3d/3d.vtx.glsl", "res/shaders/3d/3d.frg.glsl")
{
	m_Engine.m_Application.setMouseHidden(true);

	m_Shader.bind();

	m_Shader.setProjectionMatrix(glm::perspective(glm::radians(45.0f), float(m_Engine.m_Application.getWindowDimensions().x) / float(m_Engine.m_Application.getWindowDimensions().y), 0.25f, 750.0f));
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