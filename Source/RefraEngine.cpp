//TODO
    //mesh class loader (obj files)
    //model class
    //material class
    //scene class
    //resource manager class
    //application class
    //error handling class
    //event system
    //logger
//DONE
    //Camera class

#include "Render.h"
#include "Window.h"
#include "Shader.h"
#include "Texture.h"
#include "Camera.h"
#include "Input.h"
#include "MeshLoader.h"
#include "Model.h"

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

    rfe::Shader boxShader("../Assets/Shaders/cubeShaderV.vertex",
                          "../Assets/Shaders/cubeShaderF.fragment");
    boxShader.Bind();
    boxShader.SetIntUniform("text", 0);

    rfe::Texture cubeTexture("../Assets/Textures/minecraftCubeTex.jpg");

    rfe::MeshLoader loader;
    rfe::Mesh box;
    loader.LoadMesh("../Assets/Models/simpleBox.obj", box);
    box.CreateMeshVAO();
    rfe::Model cubeModel(box, boxShader);

    //texture class

    rfe::Camera camera(glm::vec3(0.0f, 0.0f,  3.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f,  0.0f), 3.0f);
    camera.SetCursorFPS(window);

    glm::mat4 projection = camera.PerspectiveMatrix(60.0f,(float) window.ScreenWidth / (float) window.ScreenHeight,
                                            0.1f, 100.0f);
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
        boxShader.Bind();

        boxShader.SetMatrix4fUniform("view", view);
        boxShader.SetMatrix4fUniform("projection", projection);
        cubeModel.SetupShaderModelMatrix();
        cubeModel.DrawModel(boxShader);

        window.SwapBuffers();

        glfwPollEvents();
    }

    window.Destroy();

    return 0;
}