QT_VERSION = 4
QT += core gui widgets opengl

LIBS += -lGLEW -lGL

QMAKE_CXXFLAGS += --std=c++11

greaterThan(QT_MAJOR_VERSION, 4):

TARGET = BSP
TEMPLATE = app

INCLUDEPATH += glm

OTHER_FILES = simple.vert simple.frag

SOURCES += main.cpp\
    MainWindow.cpp \
    GLWidget.cpp \
    Triangle.cpp \
    Vector3.cpp \
    Matrix4.cpp \
    Vector4.cpp \
    Quaternion.cpp \
    Shader.cpp \
    ShaderProgram.cpp \
    VAO.cpp \
    VBO.cpp \
    IGLBindable.cpp \
    Camera.cpp \
    Plane.cpp \
    Segment.cpp \
    Input.cpp \
    Math.cpp

HEADERS  += MainWindow.h \
    GLWidget.h \
    Triangle.h \
    Vector3.h \
    Matrix4.h \
    Vector4.h \
    Quaternion.h \
    Shader.h \
    ShaderProgram.h \
    VAO.h \
    VBO.h \
    IGLIdable.h \
    IGLBindable.h \
    Camera.h \
    Plane.h \
    Segment.h \
    Input.h \
    Math.h

FORMS += MainWindow.ui
