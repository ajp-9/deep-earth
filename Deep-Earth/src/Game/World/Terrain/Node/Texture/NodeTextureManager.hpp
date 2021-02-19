#pragma once

#include "../../../../../Engine/Renderer/Model/Texture/TextureArray.hpp"

namespace node::texture
{
	enum
	{
		grass,
		grass_side,
		dirt,
		sand,
		stone
	};
}

class NodeTextureManager
{
public:

	NodeTextureManager();

	static float getWCoord(byte id);

private:

	engine::TextureArray m_TextureArray = engine::TextureArray(256, 16);
};
