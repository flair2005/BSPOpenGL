#include "ShaderProgram.h"

ShaderProgram::ShaderProgram() : m_vshader(nullptr), m_fshader(nullptr)
{
    m_idGL = glCreateProgram();
}

ShaderProgram::ShaderProgram(const std::string &vshaderPath,
                             const std::string &fshaderPath) : ShaderProgram()
{
    Shader *vs = new Shader(Shader::Type::Vertex, vshaderPath);
    BindVertexShader(vs);
    Shader *fs = new Shader(Shader::Type::Fragment, fshaderPath);
    BindFragmentShader(fs);
    Link();
}

ShaderProgram::~ShaderProgram()
{
    glDeleteProgram(m_idGL);
}

void ShaderProgram::BindVertexShader(Shader *vshader)
{
    this->m_vshader = vshader;
}

void ShaderProgram::BindFragmentShader(Shader *fshader)
{
    this->m_fshader = fshader;
}

bool ShaderProgram::Link()
{
    if (!m_vshader)
    {
        std::cerr << "Vertex shader not set. Can't link shader program." << std::endl;
        return false;
    }

    if (!m_fshader)
    {
        std::cerr << "Fragment shader not set. Can't link shader program." << std::endl;
        return false;
    }

    glAttachShader(m_idGL, m_vshader->GetGLId());
    glAttachShader(m_idGL, m_fshader->GetGLId());

    glLinkProgram(m_idGL);

    GLint linked;
    glGetProgramiv(m_idGL, GL_LINK_STATUS, &linked);
    if (!linked)
    {
       GLint errorLength = 0;
       glGetProgramiv(m_idGL, GL_INFO_LOG_LENGTH, &errorLength);

       if (errorLength > 1)
        {
          char* errorLog = (char*) (malloc(sizeof(char) * errorLength));
          glGetProgramInfoLog(m_idGL, errorLength, NULL, errorLog);

          std::string errorStr(errorLog);
          std::cerr << "Can't link " << std::endl << this << std::endl <<
                       "   Reason:  " << errorStr << std::endl;
        }

        glDeleteProgram(m_idGL);
    }

    return linked;
}

bool ShaderProgram::SetUniformFloat(const std::string &name, float v, bool warn) const
{
    int location = GetUniformLocation(name);
    if (location >= 0)
    {
        Bind();
        glUniform1fv(location, 1, &v);
        UnBind();
    }
    else
    {
        if (warn) std::cerr << "Couldn't find uniform '" + name + "' in " <<
                                std::endl << this << std::endl << " . Not setting it." << std::endl;
    }

    return (location >= 0);
}

bool ShaderProgram::SetUniformVec3 (const std::string &name, const Vector3& v, bool warn) const
{
    int location = GetUniformLocation(name);
    if (location >= 0)
    {
        Bind();
        glUniform3fv(location, 1, &v.x);
        UnBind();
    }
    else
    {
        if (warn) std::cerr << "Couldn't find uniform '" + name + "' in " <<
                                std::endl << this << std::endl << " . Not setting it." << std::endl;
    }

    return (location >= 0);
}

bool ShaderProgram::SetUniformVec4 (const std::string &name, const Vector4& v, bool warn) const
{
    int location = GetUniformLocation(name);
    if (location >= 0)
    {
        Bind();
        glUniform4fv(location, 1, &v.x);
        UnBind();
    }
    else
    {
        if (warn) std::cerr << "Couldn't find uniform '" + name + "' in " <<
                                std::endl << this << std::endl << " . Not setting it." << std::endl;
    }

    return (location >= 0);
}

bool ShaderProgram::SetUniformMat4 (const std::string &name, const Matrix4& m, bool warn) const
{
    int location = GetUniformLocation(name);
    if (location >= 0)
    {
        Bind();
        glUniformMatrix4fv(location, 1, GL_FALSE, m.GetFirstAddress());
        UnBind();
    }
    else
    {
        if (warn) std::cerr << "Couldn't find uniform '" + name + "' in " <<
                                std::endl << this << std::endl << " . Not setting it." << std::endl;
    }

    return (location >= 0);
}

Shader *ShaderProgram::GetVertexShader() const
{
    return m_vshader;
}

Shader *ShaderProgram::GetFragmentShader() const
{
    return m_fshader;
}

GLint ShaderProgram::GetUniformLocation(const std::string &name) const
{
    return glGetUniformLocation(m_idGL, name.c_str());
}

GLint ShaderProgram::GetAttribLocation(const std::string &name) const
{
    return glGetAttribLocation(m_idGL, name.c_str());
}

const std::string ShaderProgram::ToString() const
{
    std::ostringstream oss;
    oss << "Shader program: " << std::endl <<
           "   " << m_vshader << std::endl <<
           "   " << m_fshader << std::endl;
    return oss.str();
}

void ShaderProgram::Bind() const
{
    PreBind(GL_CURRENT_PROGRAM);
    glUseProgram(m_idGL);
}

void ShaderProgram::UnBind() const
{
    glUseProgram(PreUnBind(GL_CURRENT_PROGRAM));
}

