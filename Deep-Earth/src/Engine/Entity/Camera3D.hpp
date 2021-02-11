#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
namespace engine
{
	struct Camera3D
	{
		glm::mat4 getViewMatrix()
		{
			return glm::lookAt(m_Position, m_Position + m_Front, m_Up);
		}

	protected:

		glm::vec3 m_Position = glm::vec3(0.0f, 0.0f, 0.0f);

		// z up, left-handed
		glm::vec3 m_Front = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::vec3 m_Right = glm::vec3(1.0f, 0.0f, 0.0f);
		glm::vec3 m_Up = glm::vec3(0.0f, 0.0f, 1.0f);

		float fov;
		const float SENSITIVITY = 0.1f;

		enum move
		{
			FORWARD,
			BACKWARD,
			LEFT,
			RIGHT,
			UP,
			DOWN
		};
	};
}
