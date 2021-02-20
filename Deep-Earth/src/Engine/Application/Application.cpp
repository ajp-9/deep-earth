#include "Application.hpp"

#include <iostream>

namespace engine
{
    Application::Application(const char* name, glm::ivec2 dimensions)
        : m_Dimensions(dimensions)
    {
        if (!glfwInit())
            std::cout << "Application: GLFW was not initialized!\n";

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // glfw window creation
        // --------------------
        m_Window = glfwCreateWindow(dimensions.x, dimensions.y, name, NULL, NULL);
        if (m_Window == NULL)
        {
            std::cout << "Application: Failed to create GLFW window" << std::endl;
            glfwTerminate();
        }

        glfwSetWindowPos(m_Window, 30, 50);

        glfwMakeContextCurrent(m_Window);

        // glad: load all OpenGL function pointers
        // ---------------------------------------
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Application: Failed to initialize GLAD" << std::endl;
        }

        setOpenGLSettings();

        glfwSwapInterval(1);
    }

    Application::~Application()
    {
        glfwTerminate();
    }

    bool Application::update()
    {

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(m_Window);
        glfwPollEvents();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        return !glfwWindowShouldClose(m_Window);
    }

    bool Application::isLeftMouseBtnClicked()
    {
        if (glfwGetMouseButton(m_Window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
            return true;
        else
            return false;
    }

    bool Application::isRightMouseBtnClicked()
    {
        if (glfwGetMouseButton(m_Window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
            return true;
        else
            return false;
    }

    bool Application::getInput(int key)
    {
        return glfwGetKey(m_Window, key);
    }

    glm::vec2 Application::getMousePosition()
    {
        glm::dvec2 mousePosition = glm::dvec2();
        glfwGetCursorPos(m_Window, &mousePosition.x, &mousePosition.y);

        glfwSetCursorPos(m_Window, 0, 0);

        return mousePosition;
    }

    glm::ivec2 Application::getWindowDimensions()
    {
        glm::ivec2 dimensions = m_Dimensions;

        glfwGetWindowSize(m_Window, &dimensions.x, &dimensions.y);

        return dimensions;
    }

    void Application::setMouseHidden(bool hide)
    {
        if (hide)
        {
            glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            glfwSetCursorPos(m_Window, 0, 0);
        }
        else
        {
            glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
    }

    void Application::makeFullscreen()
    {

    }
    
    void Application::setOpenGLSettings()
    {
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
    }
}
