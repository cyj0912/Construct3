#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <GLGameWindow.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QOpenGLWindow* glWindow = new GLGameWindow;
    QWidget* container = QWidget::createWindowContainer(glWindow);
    container->setFocusPolicy(Qt::TabFocus);
    ui->horizontalLayout->addWidget(container);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionExit_triggered()
{
    this->close();
}
