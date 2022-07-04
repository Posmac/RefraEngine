#ifndef REFRAENGINE_SHADER_H
#define REFRAENGINE_SHADER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>

#include "Render.h"

namespace rfe
{
    class Shader
    {
    private:
        unsigned int shaderID;
        std::map<std::string, int> uniformsData;
    public:
        Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath,
               const std::string& geometryShaderPath = std::string());

        //activation section
        void Bind();
        void Unbind();

        //setting uniforms section
        void SetVector3fUniform(const std::string& name, const glm::vec3 v);
        void SetMatrix4fUniform(const std::string& name, const glm::mat4& m);
        void SetIntUniform(const std::string& name, int i);

    private:
        void GenerateShader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath,
                            const std::string& geometryShaderPath = std::string());
        unsigned int CreateShader(const std::string& path, unsigned int shaderType, const std::string& shaderName);
        void CreateShaderProgram(unsigned int vertexShaderID, unsigned int fragmentShaderID,
                                         unsigned int geometryShaderID = 0);
        void CheckShaderGenerationErrors(unsigned int shaderId, const std::string& shaderType);
        void CheckShaderProgramGenerationErrors();
        int GetUniformLocation(const std::string& name);
    };
}

#endif //REFRAENGINE_SHADER_H
