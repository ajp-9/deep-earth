#pragma once

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include "TypeDefs.hpp"

namespace engine::math
{
	struct TransMatrix
	{
		static glm::mat4 createTransformationMatrix(glm::vec3 translation, glm::vec3 rotation, float scale);
		static glm::mat4 createTransformationMatrix(glm::vec3 translation, glm::vec3 rotation);
		static glm::mat4 createTransformationMatrix(glm::vec3 translation);
	};

	struct DimensionalAndFlat
	{
		// Vec will start from zero, size will not
		inline static uint getFlatFrom3D(glm::ivec3 vec, uint size)
		{
			return vec.x + vec.y * size + vec.z * size * size;
		}

		// Flat will start from zero, size will not
		inline static glm::ivec3 get3DFromFlat(uint flat, uint size)
		{
			return glm::ivec3(flat % size, (flat / size) % size, flat / (size * size));
		}
	};
}
