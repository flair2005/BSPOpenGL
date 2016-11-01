#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix4.h"
#include "IGLBindable.h"

class ShaderProgram : public IGLIdable
                     ,public IGLBindable
                     ,public IToString
{
private:
    Shader *m_vshader;
    Shader *m_fshader;

public:
    ShaderProgram();
    ShaderProgram(const std::string &vshaderPath,
                  const std::string &fshaderPath);
    virtual ~ShaderProgram();

    void BindVertexShader(Shader *vshader);
    void BindFragmentShader(Shader *fshader);

    bool Link();

    void Bind() const override;
    void UnBind() const override;

    bool SetUniformFloat   (const std::string &name, float v,                bool warn = false) const;
    bool SetUniformVec3    (const std::string &name, const Vector3& v,       bool warn = false) const;
    bool SetUniformVec4    (const std::string &name, const Vector4& v,       bool warn = false) const;
    bool SetUniformMat4    (const std::string &name, const Matrix4& m,       bool warn = false) const;

    Shader* GetVertexShader() const;
    Shader* GetFragmentShader() const;

    GLint GetUniformLocation(const std::string &name) const;
    GLint GetAttribLocation(const std::string &name) const;

    const std::string ToString() const override;
};

#endif // SHADERPROGRAM_H
