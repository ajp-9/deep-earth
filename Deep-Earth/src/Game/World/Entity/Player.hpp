#pragma once

#include "../../../Engine/Entity/Camera3D.hpp"
#include "../../../Engine/Application/Application.hpp"

class Player : public engine::Camera3D
{
public:

	Player(glm::vec3 position);

	void update(engine::Application& application);

private:

	void tryKeyPress(engine::Application& application);
	void tryMoveMouse(engine::Application& application);
	void move(int direction);

    bool firstMouse = true;

    const float SPEED = .1f;
    const float FAST_SPEED = 3.0f;
    const float SENSITIVITY = .05f; // change this value to your liking

    float m_CurrentSpeed = SPEED;
    float yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
    float pitch = 0.0f;
    float lastX = 800.0f / 2.0;
    float lastY = 600.0 / 2.0;
};
