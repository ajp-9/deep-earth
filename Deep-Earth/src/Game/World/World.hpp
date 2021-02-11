#pragma once

#include "../../Engine/Renderer/Renderer.hpp"
#include "Terrain/Node/NodeManager.hpp"
#include "Terrain/Terrain.hpp"
#include "../Entity/Player.hpp"

class World
{
public:

	World();
	~World();

	void render(engine::Shader3D& shader, engine::Application& app);

private:

	Terrain m_Terrain;
	Player m_Player;
};