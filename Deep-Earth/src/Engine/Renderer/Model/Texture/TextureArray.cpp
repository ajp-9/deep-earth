#include "TextureArray.hpp"

#include <glad/glad.h>
#include <stb_image.h>
#include <iostream>

namespace engine
{
    TextureArray::TextureArray(uint maxTextures, uint textureSize)
        : m_MaxTextures(maxTextures), m_TextureSize(textureSize)
    {
        glGenTextures(1, &m_ID);
        //glActiveTexture(GL_TEXTURE0);

        bind();

        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA, textureSize, textureSize, maxTextures, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
    }

    TextureArray::~TextureArray()
    {

    }

    void TextureArray::addTexture(const char* file)
    {
        // load image, create texture, and generate mipmaps
        stbi_set_flip_vertically_on_load(true);

        int width, height, nrChannels;
        unsigned char* data = stbi_load(file, &width, &height, &nrChannels, 0); // maybe change to 0 from 43
        if (data)
        {
            if (nrChannels == 4) // checks if png or not (RGBA)
            {
                glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, m_TextureCount, m_TextureSize, m_TextureSize, 1, GL_RGBA, GL_UNSIGNED_BYTE, data);
            }
            else
            {
                std::cout << "ERROR::<TextureArray::addTexture>: Only .png files are allowed!\n";
            }

            glGenerateMipmap(GL_TEXTURE_2D_ARRAY);

            glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

            glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_LOD, -1);
            glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAX_LOD, 2);

            m_TextureCount++;
        }
        else
        {
            std::cout << "Texture::Texture: File at " << file << " failed to load!\n";
        }

    }

    void TextureArray::bind()
    {
        glBindTexture(GL_TEXTURE_2D_ARRAY, m_ID);
    }
}
