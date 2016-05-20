#include "GLGameWindow.h"
#include <Render.h>
#include <Engine.h>
#include <QKeyEvent>
#include <sstream>
#include <string>
#include <functional>

using c3::FRender;
using c3::FCallablePtrCommand;
c3::FRender Render;
std::string MousePosMsg;
FCallablePtrCommand<std::function<void()>> Command;

GLGameWindow::GLGameWindow()
{
	PaintTimer = new QTimer(this);
	connect(PaintTimer, &QTimer::timeout, this, &GLGameWindow::triggerUpdate);
	PaintTimer->start(15);
}

void GLGameWindow::triggerUpdate()
{
	this->update();
}

void GLGameWindow::initializeGL()
{
    c3::RC.Render = &Render;
    Render.Init();
    c3::RC.Engine->Test();
}

void GLGameWindow::resizeGL(int w, int h)
{
	Render.Resize(w, h);
}

void GLGameWindow::paintGL()
{
	c3::RC.Engine->Update();
    Render.RenderOneFrame();
    //this->update();
}

void GLGameWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Space)
    {
        c3::RC.System->GetSystemClock()->SwitchPause();
        event->accept();
    }
    QWindow::keyPressEvent(event);
}

void GLGameWindow::mouseMoveEvent(QMouseEvent *event)
{
    event->localPos();
    std::stringstream ss;
    ss << event->x() << " " << event->y();
    MousePosMsg = ss.str();
    std::function<void()> f = std::bind(&FRender::RenderText, &Render, MousePosMsg);
    Command = FCallablePtrCommand<std::function<void()>>(f);
    Render.Push2DCommand(&Command);
    event->accept();
    QWindow::mouseMoveEvent(event);
}
