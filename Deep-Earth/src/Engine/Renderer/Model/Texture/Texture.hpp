#pragma once

#include "../../../Util/TypeDefs.hpp"
#include <string>

namespace engine
{
	class Texture
	{
	public:

		// Nearest specificies a texture paramater
		// True for nearest. False for linear
		Texture();
		Texture(const char* file, bool nearest = true);
		~Texture();

		void bind();
		
	private:

		uint m_ID;
	};
}
