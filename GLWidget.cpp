#include "GLWidget.h"

#define GLEW

#include <GL/gl.h>


GLWidget::GLWidget(QWidget *parent) : QGLWidget(parent)
{
    camera = new Camera();
    timer.start(50);
    connect(&timer, SIGNAL(timeout()), this, SLOT(Update()));
}

GLWidget::~GLWidget()
{

}

void GLWidget::initializeGL()
{
    QGLWidget::initializeGL();

    glewExperimental = GL_TRUE;
    glewInit();

    program = new ShaderProgram("simple.vert", "simple.frag");
    program->Link();
    Triangle *tri = new Triangle(Vector3(0.5f,  -0.5f,  -3.0f),
                                 Vector3(0.0f,   0.5f,  -3.0f),
                                 Vector3(-0.5f, -0.5f,  -3.0f));
    tri->Update();
    triangles.push_back(tri);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    glClearColor(0.5, 0.5, 0.5, 1.0);
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
        tri->Draw();
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

}
