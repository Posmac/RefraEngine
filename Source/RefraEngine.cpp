#include "Render.h"
#include "Window.h"
#include "Shader.h"
#include "Texture.h"
#include "Camera.h"
#include "Input.h"

#include "cube.h"

int main() {

    double deltaTime = 0;
    double lastTime = glfwGetTime();

    rfe::Render render;
    if (!render.InitGLWF()) return -1;

    rfe::Window window(1280, 720, "RefraEngine");
    window.SetWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    window.SetWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    window.SetContextCurrent();

    if (!window.CreationSuccess) return -1;
    if (!render.LoadGlad()) return -1;

    rfe::Input input{};
    input.SetupCallback(window);

    //camera class

    //event system
    //mesh class
    //model class
    //error handling class

    rfe::Shader cubeShader("../Assets/Shaders/cubeShaderV.vertex",
                           "../Assets/Shaders/cubeShaderF.fragment");

    //vertex data to model or render class
    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) 0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) (3 * sizeof(float)));

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //texture class
    rfe::Texture cubeTexture("../Assets/Textures/minecraftCubeTex.jpg");

    cubeShader.Bind();
    cubeShader.SetIntUniform("text", 0);

    glm::vec3 lookAtTarget = glm::vec3(0,0,0);

    glm::vec3 cameraPos     = glm::vec3(0.0f, 0.0f,  3.0f);
    glm::vec3 cameraForward = glm::vec3(0.0f, 0.0f, 1.0f);
    glm::vec3 cameraUp      = glm::vec3(0.0f, 1.0f,  0.0f);
    rfe::Camera camera(cameraPos, cameraForward, cameraUp, 3.0f);
    camera.SetCursorFPS(window);

    glm::mat4 projection = camera.PerspectiveMatrix(60.0f,(float) window.ScreenWidth / (float) window.ScreenHeight,
                                            0.1f, 100.0f);
    glm::mat4 model = glm::mat4(1.0);

    glEnable(GL_DEPTH_TEST);

    while (!window.ShouldClose()) {

        if(input.GetKeyState(rfe::KeyCode::KEY_ESCAPE) == rfe::Pressed)
        {
            window.SetWindowClose();
        }
        deltaTime = glfwGetTime() - lastTime;
        lastTime = glfwGetTime();

        glViewport(0, 0, window.ScreenWidth, window.ScreenHeight);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0, 1, 1, 1);

        camera.ProcessInput(input, deltaTime);
        camera.ProcessMouseInput(input.GetMouseData(), deltaTime, 0.1f);
        glm::mat4 view = camera.ViewMatrix();

        cubeTexture.ActivateTexture(GL_TEXTURE0);
        cubeTexture.Bind();
        cubeShader.Bind();

        model = glm::mat4(1.0);
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