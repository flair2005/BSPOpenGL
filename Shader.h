#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>


#include <sstream>
#include <fstream>
#include <iostream>

#include "IGLIdable.h"
#include "IToString.h"

class Shader : public IToString, public IGLIdable
{
public:

    enum Type
    {
        Vertex = GL_VERTEX_SHADER,
        Fragment = GL_FRAGMENT_SHADER
    };

private:
    std::string m_sourceCode;
    std::string m_filepath;
    Type m_type;

public:

    Shader(Shader::Type t);
    Shader(Shader::Type t, const std::string &shaderPath);

    bool LoadFromFile(const std::string &filepath);

    const std::string& GetSourceCode() const;
    const std::string& GetFilepath() const;
    Type GetType() const;
    const std::string ToString() const;
};

#endif // SHADER_H
