#include "Texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h> 
#include <glad/glad.h>

#include <iostream>

namespace engine
{
    Texture::Texture()
    {
        m_ID = -1;
    }

    Texture::Texture(const char* path, bool nearest)
	{

        glGenTextures(1, &m_ID);
        glBindTexture(GL_TEXTURE_2D, m_ID); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
        // set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // set texture filtering parameters

        if (nearest)
        {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        }
        else
        {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        }

        // load image, create texture and generate mipmaps
        stbi_set_flip_vertically_on_load(true);

        int width, height, nrChannels;
        unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0); // maybe change to 0 from 4
        if (data)
        {
            if (nrChannels == 4) // checks if png or not
            {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            }
            else // if else then load as .jpg (RGB) only
            {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            }
            //glGenerateMipmap(GL_TEXTURE_2D);

            //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
            //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -4);
        }
        else
        {
            std::cout << "Texture::Texture: File at " << path << " failed to load!\n";
        }
        stbi_image_free(data);
        glBindTexture(GL_TEXTURE_2D, 0);
	}

    Texture::~Texture()
    {
        glDeleteTextures(1, &m_ID);
    }

	void Texture::bind()
	{
        glBindTexture(GL_TEXTURE_2D, m_ID);
	}
}
