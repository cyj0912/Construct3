#include "GLGameWindow.h"
#include <Render.h>
#include <Engine.h>

c3::FRender Render;

GLGameWindow::GLGameWindow()
{
}

void GLGameWindow::initializeGL()
{
    Render.Init();
    c3::RuntimeContext.Engine->Test();
}

void GLGameWindow::resizeGL(int w, int h)
{
	Render.Resize(w, h);
}

void GLGameWindow::paintGL()
{
	c3::RuntimeContext.Engine->Update();
    Render.RenderOneFrame();
    this->update();
}
