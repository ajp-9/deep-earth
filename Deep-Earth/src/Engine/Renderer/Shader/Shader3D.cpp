#include "Shader3D.hpp"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace engine
{
	Shader3D::Shader3D()
		: Shader()
	{}

	Shader3D::Shader3D(const char* vtx_shader_loc, const char* frg_shader_loc)
		: Shader(vtx_shader_loc, frg_shader_loc)
	{
		bind();

		m_ModelMatLocation = glGetUniformLocation(m_ID, "model");
		m_ViewMatLocation = glGetUniformLocation(m_ID, "view");
		m_ProjectionMatLocation = glGetUniformLocation(m_ID, "projection");
	}

	void Shader3D::setModelMatrix(const glm::mat4x4& model)
	{
		glUniformMatrix4fv(m_ModelMatLocation, 1, GL_FALSE, glm::value_ptr(model));
	}

	void Shader3D::setViewMatrix(const glm::mat4x4& view)
	{
		glUniformMatrix4fv(m_ViewMatLocation, 1, GL_FALSE, glm::value_ptr(view));
	}

	void Shader3D::setProjectionMatrix(const glm::mat4x4& projection)
	{
		glUniformMatrix4fv(m_ProjectionMatLocation, 1, GL_FALSE, glm::value_ptr(projection));
	}
}
