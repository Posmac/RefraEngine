#ifndef REFRAENGINE_RENDER_H
#define REFRAENGINE_RENDER_H

#include <iostream>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace rfe
{
    class Render
    {
    public:
        bool InitGLWF();
        bool LoadGlad();
    };
}

#endif //REFRAENGINE_RENDER_H
