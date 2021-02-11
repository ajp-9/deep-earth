#include "Math.hpp"

#include <glm/gtc/matrix_transform.hpp>

namespace engine::math
{
	glm::mat4 TransMatrix::createTransformationMatrix(glm::vec3 translation, glm::vec3 rotation, float scale)
	{
		glm::mat4 matrix = glm::mat4(1.0f);

		matrix = glm::translate(matrix, translation);
		matrix = glm::rotate(matrix, (float)glm::radians(rotation.x), glm::vec3(1, 0, 0));
		matrix = glm::rotate(matrix, (float)glm::radians(rotation.y), glm::vec3(0, 1, 0));
		matrix = glm::rotate(matrix, (float)glm::radians(rotation.z), glm::vec3(0, 0, 1));
		matrix = glm::scale(matrix, glm::vec3(scale));

		return matrix;
	}

	glm::mat4 TransMatrix::createTransformationMatrix(glm::vec3 translation, glm::vec3 rotation)
	{
		glm::mat4 matrix = glm::mat4(1.0f);

		matrix = glm::translate(matrix, translation);
		matrix = glm::rotate(matrix, (float)glm::radians(rotation.x), glm::vec3(1, 0, 0));
		matrix = glm::rotate(matrix, (float)glm::radians(rotation.y), glm::vec3(0, 1, 0));
		matrix = glm::rotate(matrix, (float)glm::radians(rotation.z), glm::vec3(0, 0, 1));

		return matrix;
	}

	glm::mat4 TransMatrix::createTransformationMatrix(glm::vec3 translation)
	{
		glm::mat4 matrix = glm::mat4(1.0f);

		matrix = glm::translate(matrix, translation);

		return matrix;
	}
}
