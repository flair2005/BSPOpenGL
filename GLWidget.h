#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <GL/glew.h>

#include <QTimer>
#include <QKeyEvent>
#include <QtOpenGL/QGLWidget>

#include "Input.h"
#include "Plane.h"
#include "Camera.h"
#include "Triangle.h"

class GLWidget : public QGLWidget
{
    Q_OBJECT

private:
    bool seePlanes = true;

public:
    GLWidget(QWidget *parent = 0);
    virtual ~GLWidget();

    QTimer timer;

    std::list<Triangle*> triangles;
    std::list<Plane*> planes;

    ShaderProgram *program = nullptr;
    Camera *camera = nullptr;

    void keyPressEvent(QKeyEvent *ev) override;
    void keyReleaseEvent(QKeyEvent *ev) override;
    void mouseDoubleClickEvent(QMouseEvent *ev) override;
    void mouseMoveEvent(QMouseEvent *ev) override;
    void mousePressEvent(QMouseEvent *ev) override;
    void mouseReleaseEvent(QMouseEvent *ev) override;
    void wheelEvent(QWheelEvent *ev) override;

    static int GetWidth();
    static int GetHeight();

    static GLWidget *GetInstance();

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int width, int height) override;

private:
    static GLWidget *instance;
    Input *input = nullptr;

public slots:
    void Update();
    void OnSeePlanesToggled(bool v);
};

#endif // GLWIDGET_H
