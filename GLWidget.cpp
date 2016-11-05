#include "GLWidget.h"

#define GLEW

#include <GL/gl.h>

#include "Math.h"
#include "Plane.h"

GLWidget *GLWidget::instance = nullptr;

GLWidget::GLWidget(QWidget *parent) : QGLWidget(parent)
{
    srand(time(nullptr));

    camera = new Camera();

    timer.start(50);
    connect(&timer, SIGNAL(timeout()), this, SLOT(Update()));

    GLWidget::instance = this;
    input = new Input();

    setMouseTracking(true);
    setFocusPolicy(Qt::ClickFocus);
}

GLWidget::~GLWidget()
{
    if (bspRoot) { delete bspRoot; }
}

void GLWidget::keyPressEvent(QKeyEvent *ev)
{
    input->EnqueueEvent(ev);
    QGLWidget::keyPressEvent(ev);
}

void GLWidget::keyReleaseEvent(QKeyEvent *ev)
{
    input->EnqueueEvent(ev);
    QGLWidget::keyReleaseEvent(ev);
}

void GLWidget::mouseDoubleClickEvent(QMouseEvent *ev)
{
    input->EnqueueEvent(ev);
    QGLWidget::mouseDoubleClickEvent(ev);
}

void GLWidget::mouseMoveEvent(QMouseEvent *ev)
{
    input->EnqueueEvent(ev);
    QGLWidget::mouseMoveEvent(ev);
}

void GLWidget::mousePressEvent(QMouseEvent *ev)
{
    input->EnqueueEvent(ev);
    QGLWidget::mousePressEvent(ev);
}

void GLWidget::mouseReleaseEvent(QMouseEvent *ev)
{
    input->EnqueueEvent(ev);
    QGLWidget::mouseReleaseEvent(ev);
}

void GLWidget::wheelEvent(QWheelEvent *ev)
{
    input->EnqueueEvent(ev);
    QGLWidget::wheelEvent(ev);
}

int GLWidget::GetWidth()
{
    return GLWidget::GetInstance()->width();
}

int GLWidget::GetHeight()
{
    return GLWidget::GetInstance()->height();
}

GLWidget *GLWidget::GetInstance()
{
    return GLWidget::instance;
}

void GLWidget::initializeGL()
{
    QGLWidget::initializeGL();

    glewExperimental = GL_TRUE;
    glewInit();

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    program = new ShaderProgram("simple.vert", "simple.frag");
    program->Link();

    std::list<Triangle*> triangles;
    // Overlapped triangles scene
    const float S = 25.0f;
    const float D1 = -S, D2 =  0, D3 =  S;
    Triangle *tri1 = new Triangle(Vector3( S,    0, D2), Vector3( S*2,    0, D2), Vector3(   0,    S*2,  D2)); tri1->RefreshData();
    Triangle *tri2 = new Triangle(Vector3(-S,    0, D2), Vector3(-S*2,    0, D2), Vector3( S*2,    S*2,  D3)); tri2->RefreshData();
    Triangle *tri3 = new Triangle(Vector3(-S, -S/4, D3), Vector3(  -S,  S/2, D3), Vector3( S*2,    S/2,  D1)); tri3->RefreshData();
    triangles = {tri1, tri2, tri3};
    camera->position += camera->GetForward() * 40.0f;
    //

    bspRoot = BSPNode::ConstructBSPTree(triangles);

    randomSceneNumTriangles = 1;
    GenerateRandomScene();

    glClearColor(0,0,0,1);
}

void GLWidget::paintGL()
{
    QGLWidget::paintGL();

    program->Bind();

    program->SetUniformMat4("projection", camera->GetProjection());
    program->SetUniformMat4("view", camera->GetView());

    if (drawWithDepthTest)
    {
        glEnable(GL_DEPTH_TEST);
        glClear(GL_DEPTH_BUFFER_BIT);
    }
    else
    {
        glDisable(GL_DEPTH_TEST);
    }

    glClear(GL_COLOR_BUFFER_BIT);

    BSPNode::renderStep = 0;
    bspRoot->Render(camera->position, program);

    program->UnBind();
}

void GLWidget::Update()
{
    //processEvents();
    input->ProcessEnqueuedEvents();

    camera->Update();
    update();
    input->OnFrameFinished();
}

void GLWidget::GenerateRandomScene()
{
    if (bspRoot) { delete bspRoot; }

    std::list<Triangle*> triangles;

    for (int i = 0; i < randomSceneNumTriangles; ++i)
    {
        int size = Math::RandAbs() * randomSceneNumTriangles / 2 + 20;
        Vector3 v1 = Vector3(Math::Rand(), Math::Rand(), Math::Rand()).Normalized() * size;
        Vector3 v2 = Vector3(Math::Rand(), Math::Rand(), Math::Rand()).Normalized() * size;
        Vector3 v3 = Vector3(Math::Rand(), Math::Rand(), Math::Rand()).Normalized() * size;
        Vector3 center = Vector3(Math::Rand(), Math::Rand(), Math::Rand()) * randomSceneNumTriangles / 2;

        Triangle *tri = new Triangle(center + v1, center + v2, center + v3);
        triangles.push_back(tri);
    }

    bspRoot = BSPNode::ConstructBSPTree(triangles);
}

void GLWidget::OnSeePlanesToggled(bool v)
{
    seePlanes = v;
}

void GLWidget::OnSeeTriDivisionsToggled(bool v)
{
    seeTriDivisions = v;
}

void GLWidget::OnDrawWithDepthTestToggled(bool v)
{
    drawWithDepthTest = v;
}

void GLWidget::OnRenderStepsChanged(int v)
{
    bspRenderSteps = v;
}

void GLWidget::OnRandomSceneNumTrianglesChanged(int n)
{
    randomSceneNumTriangles = n;
}


void GLWidget::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);
}
