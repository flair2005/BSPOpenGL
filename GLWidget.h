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
#include "BSPNode.h"

class GLWidget : public QGLWidget
{
    Q_OBJECT

public:
    bool seePlanes = false;
    bool seeTriDivisions = false;
    bool drawWithDepthTest = false;
    int randomSceneNumTriangles = 30;
    int bspRenderSteps = 9999999;

    GLWidget(QWidget *parent = 0);
    virtual ~GLWidget();

    QTimer timer;

    BSPNode *bspRoot = nullptr;

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
    void GenerateRandomScene();
    void OnSeePlanesToggled(bool v);
    void OnSeeTriDivisionsToggled(bool v);
    void OnDrawWithDepthTestToggled(bool v);
    void OnRenderStepsChanged(int v);
    void OnRandomSceneNumTrianglesChanged(int n);
};

#endif // GLWIDGET_H
