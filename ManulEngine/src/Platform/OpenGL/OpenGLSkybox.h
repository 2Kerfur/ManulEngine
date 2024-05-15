#pragma once
#include <vector>
#include <string>
#include <glad/glad.h>
#include "OpenGLTexture.h"
#include "OpenGLShader.h"

#include "stb_image.h"
using std::cerr;
using std::endl;
using std::string;
using std::vector;

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
class SkyBox {
    GLuint VBOvertices, VBOindices;
    unsigned int cubemapTexture;

    unsigned int loadCubemap(vector<string> faces, const string sky)
    {
        unsigned int textureID;
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

        string path = string("C:/DEV/C++/ManulEngine/out/build/x64-Release/Storforsen4/") + sky + string("/");
        M_CORE_INFO(path);
        int width, height, nrChannels;
        for (unsigned int i = 0; i < faces.size(); i++)
        {
            string file = path + faces[i];
            cerr << file << endl;

            GLubyte* data = stbi_load(file.c_str(), &width, &height, &nrChannels, 0);
            if (data)
            {
                glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                    0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
                );

                // glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
                stbi_image_free(data);
                // glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
            }
            else
            {
                M_CORE_ERROR("Cubemap texture failed to load at path: ");
                //std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
                stbi_image_free(data);
            }
        }
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

        return textureID;
    }
    void Init(const float size, const string sky) {
        GLfloat sky_vertices[] = {
            size,  size,  size,
            size, -size,  size,
            size,  size, -size,
            size, -size, -size,
           -size, -size, -size,
           -size,  size, -size,
           -size, -size,  size,
           -size,  size,  size
        };

        GLuint sky_indices[] = {
            0, 1, 3,
            3, 2, 0,
            0, 1, 7,
            7, 6, 1,
            1, 3, 6,
            6, 4, 3,
            3, 2, 4,
            4, 2, 5,
            5, 4, 6,
            6, 5, 7,
            7, 5, 2,
            2, 0, 7
        };
        vector<string> faces
        {
            "right.jpg",
            "left.jpg",
            "top.jpg",
            "bottom.jpg",
            "front.jpg",
            "back.jpg"
        };
        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &VBOvertices);
        glGenBuffers(1, &VBOindices);

        cubemapTexture = loadCubemap(faces, sky);
        glBindVertexArray(vao); //GL_CHECK_ERRORS;

        //передаем в шейдерную программу атрибут координат вершин
        glBindBuffer(GL_ARRAY_BUFFER, VBOvertices); //GL_CHECK_ERRORS;
        glBufferData(GL_ARRAY_BUFFER, sizeof(sky_vertices), sky_vertices, GL_STATIC_DRAW); //GL_CHECK_ERRORS;
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (GLvoid*)0); //GL_CHECK_ERRORS;
        glEnableVertexAttribArray(0);// GL_CHECK_ERRORS;

        //передаем в шейдерную программу индексы
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBOindices); //GL_CHECK_ERRORS;
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(sky_indices), sky_indices, GL_STATIC_DRAW); //GL_CHECK_ERRORS;

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindVertexArray(0);
    }

public:
    GLuint vao;
    void InitSkybox(const float size = 1, const string skybox = "1", GLuint VAO = 0)
    {
        vao = VAO;
        Init(size, skybox);
    }
    void Draw(OpenGLShader& shader, const glm::mat4& projection, const glm::mat4& view, const glm::vec3& campos) {
        glDepthMask(GL_FALSE);
        shader.Use();
        shader.setMat4("projection", projection);
        shader.setMat4("view", view);
        shader.setVec3("campos", campos);

        glBindVertexArray(vao);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);

        glDrawElements(GL_TRIANGLE_STRIP, 36, GL_UNSIGNED_INT, nullptr); //GL_CHECK_ERRORS;
        glBindVertexArray(0); //GL_CHECK_ERRORS;
        glDepthMask(GL_TRUE);
    }
};
