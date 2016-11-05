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

    program = new ShaderProgram("simple.vert", "simple.frag");
    program->Link();

    for (int i = 0; i < 30; ++i)
    {
        int size = Math::RandAbs() * 30 + 20;
        Vector3 v1 = Vector3(Math::Rand(), Math::Rand(), Math::Rand()).Normalized() * size;
        Vector3 v2 = Vector3(Math::Rand(), Math::Rand(), Math::Rand()).Normalized() * size;
        Vector3 v3 = Vector3(Math::Rand(), Math::Rand(), Math::Rand()).Normalized() * size;
        Vector3 center = Vector3(Math::Rand(), Math::Rand(), Math::Rand()) * 30.0f;

        Triangle *tri = new Triangle(center + v1, center + v2, center + v3);
        tri->RefreshData();

        if (bspRoot == nullptr)
        {
            bspRoot = new BSPNode(tri);
        }
        else
        {
            bspRoot->InsertTriangle(tri);
        }
    }

    /*
    for (int i = 0; i < 3; ++i)
    {
        Plane *plane = new Plane(Math::RandAbsVector3() * 30.0f, Math::RandVector3());
        std::list<Triangle*> splitTriangles;
        for (auto it = triangles.begin(); it != triangles.end(); ++it)
        {
            Triangle *tri = *it;
            Vector3 int1, int2;
            int numIntersections = tri->GetIntersectionWithPlane(*plane, &int1, &int2);
            if (numIntersections > 0)
            {
                Triangle *splitTri1, *splitTri2, *splitTri3;
                if (tri->SplitWithPlane(plane, &splitTri1, &splitTri2, &splitTri3))
                {
                    splitTriangles.push_back(splitTri1);
                    splitTriangles.push_back(splitTri2);
                    splitTriangles.push_back(splitTri3);
                }
            }
            else
            {
                splitTriangles.push_back(tri);
            }
        }
        triangles = splitTriangles;
        plane->RefreshData();
        planes.push_back(plane);
    }
    */

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    glClearColor(1.0, 1.0, 1.0, 1.0);
}

void GLWidget::paintGL()
{
    QGLWidget::paintGL();

    program->Bind();

    program->SetUniformMat4("projection", camera->GetProjection());
    program->SetUniformMat4("view", camera->GetView());

    glClear(GL_COLOR_BUFFER_BIT);
    bspRoot->Render(camera->position, program);
    /*
    for (Triangle *tri : triangles)
    {
        tri->Render(program);
    }
    */

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

void GLWidget::OnSeePlanesToggled(bool v)
{
    seePlanes = v;
}


void GLWidget::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);
}
