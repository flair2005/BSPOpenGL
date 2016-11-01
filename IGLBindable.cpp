#include "IGLBindable.h"

IGLBindable::IGLBindable() {}

void IGLBindable::PreBind(GLenum bindTarget) const
{
    if (m_target_To_BoundIdsStack.find(bindTarget) == m_target_To_BoundIdsStack.end())
    {
        m_target_To_BoundIdsStack[bindTarget] = std::stack<GLint>();
    }

    GLint currentBoundId = 0;
    glGetIntegerv(bindTarget, &currentBoundId);
    m_target_To_BoundIdsStack[bindTarget].push(currentBoundId);
}

GLint IGLBindable::PreUnBind(GLenum bindTarget) const
{
    if (m_target_To_BoundIdsStack.find(bindTarget) == m_target_To_BoundIdsStack.end() ||
        m_target_To_BoundIdsStack[bindTarget].empty())
    {
        std::cerr << "Unbinding non-binded GL target " << bindTarget << std::endl;
        return 0;
    }

    GLint id = m_target_To_BoundIdsStack[bindTarget].top();
    m_target_To_BoundIdsStack[bindTarget].pop();
    return id;
}
