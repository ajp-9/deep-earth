#pragma once

#include <entt.hpp>

#include "../../Engine/Renderer/Renderer.hpp"
#include "Terrain/Node/NodeManager.hpp"
#include "Terrain/Terrain.hpp"
#include "Entity/Player/Player.hpp"

class World
{
public:

	World();
	~World();

	void render(engine::Shader3D& shader);
	void update(engine::Application& app);

private:

	Terrain m_Terrain;
	Player m_Player;

	entt::registry m_Registry;
};
