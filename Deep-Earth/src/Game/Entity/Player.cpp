#include "Player.hpp"

Player::Player(glm::vec3 position)
{
	this->m_Position = position;
}

void Player::update(engine::Application& application)
{
    tryKeyPress(application);
    tryMoveMouse(application);
}

void Player::tryKeyPress(engine::Application& application)
{
    if (!application.getInput(GLFW_KEY_LEFT_SHIFT))
        m_CurrentSpeed = SPEED;
    else
        m_CurrentSpeed = FAST_SPEED;

    if (application.getInput(GLFW_KEY_W))
        move(FORWARD);
    if (application.getInput(GLFW_KEY_S))
        move(BACKWARD);
    if (application.getInput(GLFW_KEY_A))
        move(LEFT);
    if (application.getInput(GLFW_KEY_D))
        move(RIGHT);
    if (application.getInput(GLFW_KEY_E))
        move(UP);
    if (application.getInput(GLFW_KEY_Q))
        move(DOWN);
}

void Player::tryMoveMouse(engine::Application& application)
{
    glm::vec2 mousePos = application.getMousePosition();

    if (mousePos.x || mousePos.y)
    {
        if (firstMouse)
        {
            lastX = mousePos.x;
            lastY = mousePos.y;
            firstMouse = false;
        }

        float xoffset = mousePos.x;
        float yoffset = -mousePos.y; // reversed since y-coordinates go from bottom to top
        lastX = mousePos.x;
        lastY = mousePos.y;

        xoffset *= SENSITIVITY;
        yoffset *= SENSITIVITY;

        yaw += xoffset;
        pitch += yoffset;

        // make sure that when pitch is out of bounds, screen doesn't get flipped
        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;

        m_Front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        m_Front.z = sin(glm::radians(pitch));
        m_Front.y = -sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        m_Front = glm::normalize(m_Front);
        m_Right = glm::normalize(glm::cross(m_Front, m_Up));
    }
}

void Player::move(int direction)
{
    if (direction == FORWARD)
        m_Position += m_Front * m_CurrentSpeed;
    if (direction == BACKWARD)
        m_Position -= m_Front * m_CurrentSpeed;
    if (direction == LEFT)
        m_Position -= m_Right * m_CurrentSpeed;
    if (direction == RIGHT)
        m_Position += m_Right * m_CurrentSpeed;
    if (direction == DOWN)
        m_Position += glm::normalize(glm::cross(m_Front, m_Right)) * m_CurrentSpeed;
    if (direction == UP)
        m_Position -= glm::normalize(glm::cross(m_Front, m_Right)) * m_CurrentSpeed;
}
