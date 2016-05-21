#include "GLGameWindow.h"
#include <Render.h>
#include <Engine.h>
#include <QKeyEvent>
#include <sstream>
#include <string>
#include <functional>
#include <Game.h>

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
	c3::RC.System->GetSystemClock()->Init();
	new(&c3::Game) c3::FGame();	//Hacky fix to get around C++ constructor call ordering
	c3::RC.Render = &Render;
    Render.Init();
    c3::RC.Engine->Init();
}

void GLGameWindow::resizeGL(int w, int h)
{
	Render.Resize(w, h);
}

void GLGameWindow::paintGL()
{
	c3::RC.Engine->Update();
	c3::Game.Update();
    Render.RenderOneFrame();
    //this->update();
}

void GLGameWindow::keyPressEvent(QKeyEvent *event)
{
	switch (event->key()) {
	case Qt::Key_Space:
		c3::RC.System->GetSystemClock()->SwitchPause();
		event->accept();
	case Qt::Key_W:
		c3::Game.ActiveControls.MoveUp = true;
		c3::Game.ActiveControls.MoveDown = false;	//Neutralize opposite control
		break;
	case Qt::Key_A:
		c3::Game.ActiveControls.MoveLeft = true;
		c3::Game.ActiveControls.MoveRight = false;	//Neutralize opposite control
		break;
	case Qt::Key_S:
		c3::Game.ActiveControls.MoveDown = true;
		c3::Game.ActiveControls.MoveUp = false;	//Neutralize opposite control
		break;
	case Qt::Key_D:
		c3::Game.ActiveControls.MoveRight = true;
		c3::Game.ActiveControls.MoveLeft = false;	//Neutralize opposite control
		break;
	}
	QWindow::keyPressEvent(event);
}

void GLGameWindow::keyReleaseEvent(QKeyEvent *event)
{
	switch (event->key()) {
	case Qt::Key_W:
		c3::Game.ActiveControls.MoveUp = false;
		break;
	case Qt::Key_A:
		c3::Game.ActiveControls.MoveLeft = false;
		break;
	case Qt::Key_S:
		c3::Game.ActiveControls.MoveDown = false;
		break;
	case Qt::Key_D:
		c3::Game.ActiveControls.MoveRight = false;
		break;
	}
	QWindow::keyReleaseEvent(event);
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
