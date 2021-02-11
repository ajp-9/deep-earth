#include "Renderer.hpp"

#include <glad/glad.h>
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader/Shader3D.hpp"
#include "../Util/Profile.hpp"

namespace engine
{
	Renderer::Renderer()
	{
		PROFILE_SCOPE("Renderer::Renderer");
	}

	Renderer::~Renderer() {}

	void Renderer::update()
	{
	}
}
