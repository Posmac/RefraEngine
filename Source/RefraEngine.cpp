#include <iostream>

#include "Render.h"
#include "Shader.h"
#include "Texture.h"
#include "Window.h"

#include "cube.h"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

void processInput(GLFWwindow* window, int key, int scancode, int action, int mods);

int main()
{
    rfe::Render render;
    if(!render.InitGLWF())   return -1;

    rfe::Window window (SCREEN_WIDTH, SCREEN_HEIGHT, "RefraEngine");
    window.SetWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    window.SetWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    window.SetContextCurrent();

    if(!window.CreationSuccess) return -1;
    if(!render.LoadGlad())   return -1;

    //render class
    //window class
    //input class

    //mesh class
    //model class
    //error handling class

    rfe::Shader cubeShader("../Assets/Shaders/cubeShaderV.vertex",
                           "../Assets/Shaders/cubeShaderF.fragment");

    //vertex data
    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) (3 * sizeof(float)));

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //texture class
    rfe::Texture cubeTexture("../Assets/Textures/minecraftCubeTex.jpg");

    cubeShader.Bind();
    cubeShader.SetIntUniform("text", 0);

    glm::mat4 model = glm::mat4(1.0);
    glm::vec3 cameraPos = glm::vec3(2, 2, 5);
    glm::vec3 cameraForward = glm::vec3(0, 0, -1);
    glm::vec3 cameraUp = glm::vec3(0, 1, 0);
    glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraForward, cameraUp);
    glm::mat4 projection = glm::perspective(glm::radians(60.0f), (float)SCREEN_WIDTH/SCREEN_HEIGHT,
                                            0.1f, 100.0f);
    glEnable(GL_DEPTH_TEST);

    while (!window.ShouldClose())
    {
        glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0, 1, 1, 1);

        cubeTexture.ActivateTexture(GL_TEXTURE0);
        cubeTexture.Bind();
        cubeShader.Bind();

        model = glm::mat4(1.0);
        model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));

        cubeShader.SetMatrix4fUniform("model", model);
        cubeShader.SetMatrix4fUniform("view", view);
        cubeShader.SetMatrix4fUniform("projection", projection);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        window.SwapBuffers();
        glfwPollEvents();
    }

    window.Destroy();

    return 0;
}