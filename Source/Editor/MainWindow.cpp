#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <GLGameWindow.h>
#include <Core.h>
#include <IRender.h>
#include <Engine/Public/Game.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QOpenGLWindow* glWindow = new GLGameWindow;
    QWidget* container = QWidget::createWindowContainer(glWindow);
    container->setFocusPolicy(Qt::TabFocus);
    ui->horizontalLayout->addWidget(container);
    ui->horizontalLayout->setMargin(0);

	ui->logText->setLineWrapMode(QPlainTextEdit::NoWrap);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionExit_triggered()
{
    this->close();
}

void MainWindow::on_actionReloadShader_triggered()
{
    c3::RC.Render->SetFlag(c3::IRender::EFlag::ReloadShader, true);
}

void MainWindow::on_actionNearFar_triggered()
{
    c3::RC.Render->SetFlag(c3::IRender::EFlag::SwitchNearFar, true);
}

void MainWindow::OnLogChanged()
{
	ui->logText->appendPlainText(c3::FLog::ReadBuffer().c_str());
}