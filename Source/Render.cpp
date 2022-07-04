#include "Render.h"

bool rfe::Render::InitGLWF()
{
    if (!glfwInit())
    {
        std::cout << "Initialization failed " << '\n';
        glfwTerminate();
        return false;
    }
    return true;
}

bool rfe::Render::LoadGlad()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return false;
    }
    return true;
}
