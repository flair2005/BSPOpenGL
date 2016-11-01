#ifndef VAO_H
#define VAO_H

#include <GL/glew.h>
#include <vector>
#include <map>

#include "VBO.h"
#include "ShaderProgram.h"

class VAO : public IGLIdable, IGLBindable
{
private:

    std::vector<const VBO*> m_vbos;

public:

    VAO();
    virtual ~VAO();

    void BindVBO(const VBO *vbo,
                 GLint location,
                 GLint dataComponentsCount = -1,
                 GLenum dataType           = GL_FLOAT,
                 GLboolean dataNormalized  = GL_FALSE,
                 GLsizei dataStride        = 0,
                 GLuint dataOffset         = 0);

    void UnBindVBO(GLint location);

    void Bind() const override;
    void UnBind() const override;

    const VBO *GetVBOByLocation(int location) const;

    int GetVBOCount() const;
};

#endif // VAO_H
