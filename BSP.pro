#-------------------------------------------------
#
# Project created by QtCreator 2016-11-01T21:24:21
#
#-------------------------------------------------

QT_VERSION = 4
QT += core gui widgets opengl

LIBS += -lGLEW -lGL

QMAKE_CXXFLAGS += --std=c++11

greaterThan(QT_MAJOR_VERSION, 4):

TARGET = BSP
TEMPLATE = app

INCLUDEPATH += glm

SOURCES += main.cpp\
        MainWindow.cpp \
    GLWidget.cpp \
    Triangle.cpp \
    Vector3.cpp \
    Matrix4.cpp \
    Vector4.cpp \
    Quaternion.cpp

HEADERS  += MainWindow.h \
    GLWidget.h \
    Triangle.h \
    Vector3.h \
    Matrix4.h \
    Vector4.h \
    Quaternion.h

FORMS    += MainWindow.ui
