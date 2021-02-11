#pragma once

#include "Shader.hpp"
#include "../../Util/TypeDefs.hpp"

namespace engine
{
	struct Shader3D : public Shader
	{
		Shader3D();
		Shader3D(const char* vtx_shader_loc, const char* frg_shader_loc);

		// Should be called every frame.
		// Shader NEEDS to be binded first. 
		void setModelMatrix(const glm::mat4x4& model);

		// Should change when camera moves.
		// Shader NEEDS to be binded first.
		void setViewMatrix(const glm::mat4x4& view);

		// Should only change when changing fov, aspect ratio, and clipping distance.
		// Shader NEEDS to be binded first.
		void setProjectionMatrix(const glm::mat4x4& projection);

	private:
	
		uint m_ModelMatLocation;
		uint m_ViewMatLocation;
		uint m_ProjectionMatLocation;
	};
}
