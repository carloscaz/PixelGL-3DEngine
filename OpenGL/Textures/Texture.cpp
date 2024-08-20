#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION

#include <iostream>
#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include "stb_image/stb_image.h"

Texture::Texture()
{
}

Texture* Texture::Load(const char* _filename)
{
    Texture* texture = new Texture();

    //Bind texture data in OpenGL
    glGenTextures(1, &texture->m_tex);
    glBindTexture(GL_TEXTURE_2D, texture->m_tex);

    //Configure Texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    stbi_set_flip_vertically_on_load(true);
    int nrChannels;
    unsigned char* data = stbi_load(_filename, &texture->m_width, &texture->m_height, &nrChannels,0);
    if (data)
    {
        if (nrChannels == 4) //If 4 channels, image with RGBA
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture->m_width, texture->m_height, 0,
                         GL_RGBA, GL_UNSIGNED_BYTE, data);
        }
        else if (nrChannels == 3) //If 3 channels, image with RGB
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture->m_width, texture->m_height, 0, GL_RGB,
                         GL_UNSIGNED_BYTE, data);
        }
        else if (nrChannels == 2) //If 2 channels, image with RG
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RG, texture->m_width, texture->m_height, 0, GL_RG,
                         GL_UNSIGNED_BYTE, data);
        }
        else //Image with R
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, texture->m_width, texture->m_height, 0, GL_RED,
                         GL_UNSIGNED_BYTE, data);
        }
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    else
    {
        std::cout << "Texture not found" << std::endl;
    }

    stbi_image_free(data);

    return texture;
}

unsigned int Texture::GetId()
{
    return m_tex;
}
