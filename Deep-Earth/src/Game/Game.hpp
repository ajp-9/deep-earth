#pragma once

#include "../Engine/Engine.hpp"
#include "World/World.hpp"

class Game
{
public:

	Game();

	void run();

private:

	engine::Engine m_Engine;
	engine::Shader3D m_Shader;

	World m_World;
};