#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <GL/glew.h>

#include <QTimer>
#include <QtOpenGL/QGLWidget>


#include "Camera.h"
#include "Triangle.h"

class GLWidget : public QGLWidget
{
    Q_OBJECT

public:
    GLWidget(QWidget *parent = 0);
    virtual ~GLWidget();

    QTimer timer;

    std::list<Triangle*> triangles;

    ShaderProgram *program = nullptr;
    Camera *camera = nullptr;

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int width, int height) override;

public slots:
    void Update();
};

#endif // GLWIDGET_H
