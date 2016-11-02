#include "GLWidget.h"

#define GLEW

#include <GL/gl.h>

#include "Plane.h"

GLWidget::GLWidget(QWidget *parent) : QGLWidget(parent)
{
    srand(time(nullptr));

    camera = new Camera();

    timer.start(50);
    connect(&timer, SIGNAL(timeout()), this, SLOT(Update()));

    setFocusPolicy(Qt::ClickFocus);
}

GLWidget::~GLWidget()
{

}

float GLWidget::Rand()
{
    return ( rand() % 1000 - 500) / 500.0f;
}

float GLWidget::RandAbs()
{
    return Rand() * 0.5f + 0.5f;
}

void GLWidget::keyPressEvent(QKeyEvent *ev)
{
    QGLWidget::keyPressEvent(ev);
    camera->OnKeyPressedEvent(ev);
}

void GLWidget::initializeGL()
{
    QGLWidget::initializeGL();

    glewExperimental = GL_TRUE;
    glewInit();

    program = new ShaderProgram("simple.vert", "simple.frag");
    program->Link();

    for (int i = 0; i < 1; ++i)
    {
        int size = RandAbs() * 50 + 30;
        Vector3 v1 = Vector3(Rand(), Rand(), Rand()).Normalized() * size;
        Vector3 v2 = Vector3(Rand(), Rand(), Rand()).Normalized() * size;
        Vector3 v3 = Vector3(Rand(), Rand(), Rand()).Normalized() * size;
        Vector3 center = Vector3(Rand(), Rand(), Rand()) * 0.0f;

        Triangle *tri = new Triangle(center + v1, center + v2, center + v3);
        tri->RefreshData();

        triangles.push_back(tri);
    }

    Plane *plane = new Plane(Vector3::Zero, Vector3(Rand(), Rand(), Rand()));
    std::list<Triangle*> splitTriangles;
    for (auto it = triangles.begin(); it != triangles.end(); ++it)
    {
        Triangle *tri = *it;
        Vector3 int1, int2;
        int numIntersections = tri->GetIntersectionWithPlane(*plane, &int1, &int2);
        if (numIntersections > 0)
        {
            std::cout << numIntersections << std::endl;
            tri->color = Vector4(0,1,1,1);
            Triangle *splitTri1, *splitTri2, *splitTri3;
            if (tri->SplitWithPlane(plane, &splitTri1, &splitTri2, &splitTri3))
            {
                splitTriangles.push_back(splitTri1);
                splitTriangles.push_back(splitTri2);
                splitTriangles.push_back(splitTri3);
                splitTri1->color = Vector4(0,1,0,1);
                splitTri2->color = Vector4(0,0,1,1);
                splitTri3->color = Vector4(1,0,1,1);
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

    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    glClearColor(1.0, 1.0, 1.0, 1.0);
}

void GLWidget::paintGL()
{
    QGLWidget::paintGL();

    program->Bind();

    program->SetUniformMat4("projection", camera->GetProjection());
    program->SetUniformMat4("view", camera->GetView());

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    for (Triangle *tri : triangles)
    {
        tri->Draw(program);
    }

    for (Plane *plane : planes)
    {
        plane->Draw(program);
    }

    program->UnBind();
}

void GLWidget::Update()
{
    camera->Update();
    update();
}


void GLWidget::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);
}
