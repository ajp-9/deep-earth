#include "Engine.hpp"
#include "Util/Profile.hpp"

namespace engine
{
	Engine::Engine()
	{

	}

	void Engine::update()
	{
		if (!m_Application.update())
			m_Running = false;

		m_Renderer.update();
	}
}
