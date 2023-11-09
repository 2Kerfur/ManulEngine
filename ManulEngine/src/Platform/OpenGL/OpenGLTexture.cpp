#include "OpenGLTexture.h"
#include "ManulEngine/ResourceManager/ResourceManager.h"
#include "glad/glad.h"
#include "stb_image.h"

bool OpenGLTexture::Create(std::string path)
{
    glGenTextures(1, &ID);
    stbi_set_flip_vertically_on_load(true);

    std::string imagePath = ResourceManager::GetWorkingDirectory() + "\\amogus.png";
    unsigned char* imageData = stbi_load(imagePath.c_str(), &width, &height, &nrChannels, 0);
    if (imageData)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        M_CORE_ERROR("Failed to load image");
        return false;
    }
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    stbi_image_free(imageData);

	return true;
}

void OpenGLTexture::Bind()
{
    glBindTexture(GL_TEXTURE_2D, ID);
}
