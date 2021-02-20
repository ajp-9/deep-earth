#include "Player.hpp"

Player::Player(glm::vec3 position)
{
	this->m_Position = position;
}

void Player::update(engine::Application& application, ChunkManager& chunkManager)
{
    tryMouseClick(application, chunkManager);
    tryKeyPress(application);
    tryMoveMouse(application);
}

void Player::tryMouseClick(engine::Application& application, ChunkManager& chunkManager)
{
    if (application.isLeftMouseBtnClicked())
        tryBreakBlock(chunkManager);

    if (application.isRightMouseBtnClicked())
        tryPlaceBlock(chunkManager);
}

void Player::tryBreakBlock(ChunkManager& chunkManager)
{
    glm::vec3 rayPosition = m_Position;
    for (uint i = 0; i < 100U; i++)
    {
        rayPosition += m_Front * .25f;

        if (chunkManager.removeNode(rayPosition))
            break;
    }
}

void Player::tryPlaceBlock(ChunkManager& chunkManager)
{
    glm::vec3 rayPosition = m_Position;
    for (uint i = 0; i < 100U; i++)
    {
        rayPosition += m_Front * .25f;

        if (chunkManager.addNode(Node(node::sand), rayPosition))
            break;
    }
}

void Player::tryKeyPress(engine::Application& application)
{
    if (!application.getInput(GLFW_KEY_LEFT_SHIFT))
        m_CurrentSpeed = c_Speed;
    else
        m_CurrentSpeed = c_FastSpeed;

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
            m_LastX = mousePos.x;
            m_LastY = mousePos.y;
            firstMouse = false;
        }

        float xoffset = mousePos.x;
        float yoffset = -mousePos.y; // reversed since y-coordinates go from bottom to top
        m_LastX = mousePos.x;
        m_LastY = mousePos.y;

        xoffset *= c_Sensitivity;
        yoffset *= c_Sensitivity;

        m_Yaw += xoffset;
        m_Pitch += yoffset;

        // make sure that when pitch is out of bounds, screen doesn't get flipped
        if (m_Pitch > 89.0f)
            m_Pitch = 89.0f;
        if (m_Pitch < -89.0f)
            m_Pitch = -89.0f;

        m_Front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
        m_Front.z = sin(glm::radians(m_Pitch));
        m_Front.y = -sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
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
