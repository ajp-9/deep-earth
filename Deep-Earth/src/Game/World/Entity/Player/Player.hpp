#pragma once

#include "../../../../Engine/Entity/Camera3D.hpp"
#include "../../../../Engine/Application/Application.hpp"

#include "../../Terrain/Chunk/ChunkManager.hpp"

class Player : public engine::Camera3D
{
public:

	Player(glm::vec3 position);

	void update(engine::Application& application, ChunkManager& chunkManager);

    inline glm::vec3& getPosition() { return m_Position; }

private:

    void tryMouseClick(engine::Application& application, ChunkManager& chunkManager);

    void tryBreakBlock(ChunkManager& chunkManager);
    void tryPlaceBlock(ChunkManager& chunkManager);

	void tryKeyPress(engine::Application& application);
	void tryMoveMouse(engine::Application& application);
	void move(int direction);

private:

    bool firstMouse = true;

    const float c_Speed = .1f;
    const float c_FastSpeed = 2.5f;
    const float c_Sensitivity = .05f; // change this value to your liking

    const uint c_TicksWaitTimeForBreakNPlace = 8;

    uint m_TicksAgoBreak = 0;
    uint m_TicksAgoPlace = 0;

    float m_CurrentSpeed = c_Speed;
    float m_Yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
    float m_Pitch = 0.0f;
    float m_LastX = 800.0f / 2.0;
    float m_LastY = 600.0 / 2.0;
};
