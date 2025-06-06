#pragma once

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string_view>

class Shader
{
public:

    Shader(std::string_view vertexPath, std::string_view fragmentPath);
    ~Shader() { glDeleteProgram(m_id); }

    void useProgram();

    // utility uniform functions
    void setBool(std::string_view name, bool value) const;
    void setInt(std::string_view name, int value) const;
    void setFloat(std::string_view name, float value) const;
    void setMatrix4(std::string_view name, const float* matrix4);
    void setVec4(std::string_view name, const float* vec4);

private:
    GLuint m_id{};

    void checkCompileErrors(GLuint shader, std::string type);


};