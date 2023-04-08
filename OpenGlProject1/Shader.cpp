#include "Shader.h"
#include <fstream>
#include <iostream>

Shader* Shader::Instance()
{
    static Shader* shader = new Shader();
    return shader;
}

GLuint Shader::GetShaderProgramID()
{
    return m_shaderProgramID;
}

bool Shader::CreateProgram()
{
    m_shaderProgramID = glCreateProgram();

    if (m_shaderProgramID == 0) {
        std::cout << "Error Creating Shader Program. " << std::endl;
        return false;
    }
    return true;
}

bool Shader::CreateShaders()
{
    m_vertextShaderID = glCreateShader(GL_VERTEX_SHADER);
    if (m_vertextShaderID == 0) {
        std::cout << "Error Creating Vertex Shader Object. " << std::endl;
        return false;
    }

    m_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    if (m_vertextShaderID == 0) {
        std::cout << "Error Creating Fragment Shader Object. " << std::endl;
        return false;
    }


    return true;
}

bool Shader::CompileShaders(const std::string& filename, ShaderType shaderType)
{
    std::fstream file;
    std::string text;
    std::string sourceCode;
    GLuint shaderID;

    shaderID = (shaderType == ShaderType::VERTES_SHADER) ? m_vertextShaderID : m_fragmentShaderID;

    file.open(filename);
    if (!file) {
        std::cout << "Error Reading Shader File. " << std::endl;
        return false;
    }
    while (!file.eof()) {
        std::getline(file, text);
        sourceCode += text + "\n";
    }
    file.close();

    const GLchar* finalSourceCode = reinterpret_cast<const GLchar*>(sourceCode.c_str());
    glShaderSource(shaderID, 1, &finalSourceCode, nullptr);

    glCompileShader(shaderID);

    GLint errorCode;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &errorCode);

    if (errorCode == GL_TRUE) {
        std::cout << "Shader Compilation Succesful ! " << std::endl;
        return true;
    }
    else {
        GLchar errorMessage[10000];
        GLsizei bufferSize = 10000;

        glGetShaderInfoLog(shaderID, bufferSize, &bufferSize, errorMessage);
        std::cout << errorMessage << std::endl;
        return false;
    }

    return true;
}

void Shader::AttachShaders()
{
    glAttachShader(m_shaderProgramID, m_vertextShaderID);
    glAttachShader(m_shaderProgramID, m_fragmentShaderID);
}

bool Shader::LinkProgram()
{
    glLinkProgram(m_shaderProgramID);

    glUseProgram(m_shaderProgramID);

    GLint errorCode;
    glGetProgramiv(m_shaderProgramID, GL_LINK_STATUS, &errorCode);

    if (errorCode == GL_TRUE) {
        std::cout << "Shader Linking Succesful ! " << std::endl;
    }
    else {
        GLchar errorMessage[10000];
        GLsizei bufferSize = 10000;

        glGetProgramInfoLog(m_shaderProgramID, bufferSize, &bufferSize, errorMessage);
        std::cout << errorMessage << std::endl;
    }

    return true;
}

void Shader::DetachShaders()
{
    glDetachShader(m_shaderProgramID, m_vertextShaderID);
    glDetachShader(m_shaderProgramID, m_fragmentShaderID);
}

void Shader::DestroyShaders()
{
    glDeleteShader(m_vertextShaderID);
    glDeleteShader(m_fragmentShaderID);
}

void Shader::DestroyProgram()
{
    glDeleteProgram(m_shaderProgramID);
}

bool Shader::SendUniformData(const std::string& uniformName, GLint data)
{
    GLint Id = glGetUniformLocation(m_shaderProgramID, uniformName.c_str());
    if (Id == -1) {
        std::cout << "Shader variable " << uniformName << "not found or not used. " << std::endl;
        return false;
    }
    glUniform1i(Id, data);
    return true;
}

bool Shader::SendUniformData(const std::string& uniformName, GLuint data)
{
    GLint Id = glGetUniformLocation(m_shaderProgramID, uniformName.c_str());
    if (Id == -1) {
        std::cout << "Shader variable " << uniformName << "not found or not used. " << std::endl;
        return false;
    }
    glUniform1ui(Id, data);
    return true;
}

bool Shader::SendUniformData(const std::string& uniformName, GLfloat data)
{
    GLint Id = glGetUniformLocation(m_shaderProgramID, uniformName.c_str());
    if (Id == -1) {
        std::cout << "Shader variable " << uniformName << "not found or not used. " << std::endl;
        return false;
    }
    glUniform1f(Id, data);
    return true;
}

bool Shader::SendUniformData(const std::string& uniformName, GLfloat x, GLfloat y)
{
    GLint Id = glGetUniformLocation(m_shaderProgramID, uniformName.c_str());
    if (Id == -1) {
        std::cout << "Shader variable " << uniformName << "not found or not used. " << std::endl;
        return false;
    }
    glUniform2f(Id, x,y);
    return true;
}

bool Shader::SendUniformData(const std::string& uniformName, GLfloat x, GLfloat y, GLfloat z)
{
    GLint Id = glGetUniformLocation(m_shaderProgramID, uniformName.c_str());
    if (Id == -1) {
        std::cout << "Shader variable " << uniformName << "not found or not used. " << std::endl;
        return false;
    }
    glUniform3f(Id, x, y,z);
    return true;
}

bool Shader::SendUniformData(const std::string& uniformName, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
    GLint Id = glGetUniformLocation(m_shaderProgramID, uniformName.c_str());
    if (Id == -1) {
        std::cout << "Shader variable " << uniformName << "not found or not used. " << std::endl;
        return false;
    }
    glUniform4f(Id, x, y,z,w);
    return true;
}

bool Shader::SendUniformData(const std::string& uniformName, const glm::mat4& data)
{
    GLint Id = glGetUniformLocation(m_shaderProgramID, uniformName.c_str());
    if (Id == -1) {
        std::cout << "Shader variable " << uniformName << "not found or not used. " << std::endl;
        return false;
    }
    glUniformMatrix4fv(Id, 1, GL_FALSE, &data[0][0]);
    return true;
}

Shader::Shader()
{
    m_shaderProgramID = 0;
    m_vertextShaderID = 0;
    m_fragmentShaderID = 0;
}
