#pragma once

#include "Application/Application.hpp"
#include "Renderer/Renderer.hpp"

namespace engine
{
	class Engine
	{
	public:

		Engine();

		void update();

	public:

		Application m_Application = Application("Deep Earth v0.1", glm::ivec2(1200, 850));
		Renderer m_Renderer;

		bool m_Running = true;
	};
}
