#include <shader.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glad/glad.h>
#include <logger.h>
Shader::Shader() {}
Shader::Shader(const char *vertexPath, const char *fragmentPath)
{
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    loadLogger.log(LogLevel::INFO, std::string("LOAD ") + vertexPath);
    loadLogger.log(LogLevel::INFO, std::string("LOAD ") + fragmentPath);
    try
    {
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;

        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        vShaderFile.close();
        fShaderFile.close();

        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure &e)
    {
        loadLogger.log(LogLevel::ERROR, std::string("ERROR::SHADER::FILE_NOT_SUCCESFULL") + fragmentPath);
        loadLogger.log(LogLevel::ERROR, std::string("ERROR::SHADER::FILE_NOT_SUCCESFULL") + vertexPath);
    }
    const char *vShaderCode = vertexCode.c_str();
    const char *fShaderCode = fragmentCode.c_str();

    unsigned int vertex, fragment;

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    checkCompileErrors(vertex, "VERTEX");

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    checkCompileErrors(fragment, "FRAGMENT");

    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);

    glUseProgram(ID);
}

void Shader::setBool(const std::string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}
void Shader::setInt(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}
void Shader::setFloat(const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}
void Shader::use()
{
    glUseProgram(ID);
}
void Shader::checkCompileErrors(unsigned int shader, std::string type)
{
    int success;
    char infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::ostringstream errorLog; // Use ostringstream to build the error message
            errorLog << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n"
                     << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;

            compileLogger.log(LogLevel::ERROR, errorLog.str());
            exit(1);
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::ostringstream errorLog; // Use ostringstream to build the error message
            errorLog << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n"
                     << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;

            compileLogger.log(LogLevel::ERROR, errorLog.str());
            exit(1);
        }
    }
}