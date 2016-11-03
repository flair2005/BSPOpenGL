#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    glwidget = ui->glWidget;
    glwidget->focusWidget();
}

MainWindow::~MainWindow()
{
    delete ui;
}
