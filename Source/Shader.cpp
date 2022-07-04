#include "Shader.h"

rfe::Shader::Shader(const std::string &vertexShaderPath, const std::string &fragmentShaderPath,
                    const std::string &geometryShaderPath)
{
    GenerateShader(vertexShaderPath, fragmentShaderPath, geometryShaderPath);
}

void rfe::Shader::Bind()
{
    glUseProgram(shaderID);
}

void rfe::Shader::Unbind()
{
    glUseProgram(0);
}

int rfe::Shader::GetUniformLocation(const std::string& name)
{
    if(uniformsData.count(name) != 0)
    {
        return uniformsData[name];
    }
    uniformsData[name] = glGetUniformLocation(shaderID, name.data());
    return uniformsData[name];
}

void rfe::Shader::SetVector3fUniform(const std::string& name, const glm::vec3 v)
{
    glUniform3f(GetUniformLocation(name), v.x, v.y, v.z);
}

void rfe::Shader::SetMatrix4fUniform(const std::string& name, const glm::mat4& m)
{
    glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(m));
}

void rfe::Shader::SetIntUniform(const std::string& name, int i)
{
    glUniform1i(GetUniformLocation(name), i);
}

void rfe::Shader::GenerateShader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath,
                                 const std::string& geometryShaderPath)
{
    unsigned int vertexShader = CreateShader(vertexShaderPath, GL_VERTEX_SHADER, "VERTEX");
    unsigned int fragmentShader = CreateShader(fragmentShaderPath, GL_FRAGMENT_SHADER, "FRAGMENT");

    unsigned int geometryShader = -1;
    if(!geometryShaderPath.empty())
    {
        geometryShader = CreateShader(geometryShaderPath, GL_GEOMETRY_SHADER, "GEOMETRY");
    }

    CreateShaderProgram(vertexShader, fragmentShader, geometryShader);
}

unsigned int rfe::Shader::CreateShader(const std::string& path, unsigned int shaderType, const std::string& shaderName)
{
    unsigned int shader = glCreateShader(shaderType);
    if(path.empty())
    {
        return 0;
    }

    std::ifstream input (path);
    std::string shaderSource;

    if(input.is_open())
    {
        std::stringstream sstr;
        sstr << input.rdbuf();
        shaderSource = sstr.str();
    }

    const char* shaderData = shaderSource.data();
    glShaderSource(shader, 1, &shaderData, NULL);
    glCompileShader(shader);

    CheckShaderGenerationErrors(shader, shaderName);

    return shader;
}

void rfe::Shader::CreateShaderProgram(unsigned int vertexShaderID, unsigned int fragmentShaderID,
                                 unsigned int geometryShaderID)
{
    shaderID = glCreateProgram();
    glAttachShader(shaderID, vertexShaderID);
    glAttachShader(shaderID, fragmentShaderID);
    if(geometryShaderID != -1)
    {
        glAttachShader(shaderID, geometryShaderID);
    }

    glLinkProgram(shaderID);
    CheckShaderProgramGenerationErrors();
}

void rfe::Shader::CheckShaderGenerationErrors(unsigned int shaderId, const std::string& shaderType)
{
    int success;
    char infoLog[512];
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(shaderId, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::" << shaderType << "::COMPILATION_FAILED \n" << infoLog << std::endl;
    }
}

void rfe::Shader::CheckShaderProgramGenerationErrors()
{
    int success;
    char infoLog[512];
    glGetProgramiv(shaderID, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(shaderID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED \n" << infoLog << std::endl;
    }
}

