#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <GL/glew.h>

#include <QtOpenGL/QGLWidget>

class GLWidget : public QGLWidget
{
    Q_OBJECT

public:
    GLWidget(QWidget *parent = 0);
    virtual ~GLWidget();

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int width, int height) override;
};

#endif // GLWIDGET_H
