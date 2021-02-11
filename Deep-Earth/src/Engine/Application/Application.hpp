#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/vec2.hpp>

namespace engine
{
	class Application
	{
	public:

		Application(const char* name, glm::ivec2 dimensions);
		~Application();

		bool update();

		bool getInput(int key);
		glm::vec2 getMousePosition();
		glm::ivec2 getWindowDimensions();

		void setMouseHidden(bool hide);
		void makeFullscreen();

	private:

		void setOpenGLSettings();

		GLFWwindow* m_Window = nullptr;

		glm::ivec2 m_Dimensions = glm::ivec2(100, 100);
	};
}
