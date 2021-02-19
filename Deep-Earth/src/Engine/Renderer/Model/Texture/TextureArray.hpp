#pragma once

#include "../../../Util/TypeDefs.hpp"

class TextureArray
{
public:

	TextureArray(uint maxTextures, uint textureSize);
	~TextureArray();

	void addTexture(const char* file);

	void bind();

private:

	uint m_ID = 0;

	uint m_TextureCount = 0;
	uint m_MaxTextures = 0;
	uint m_TextureSize = 0;
};
