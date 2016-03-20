#pragma once
#include <QOpenGLWindow>

class GLGameWindow : public QOpenGLWindow
{
public:
    GLGameWindow();

protected:
    virtual void initializeGL() override;
    virtual void resizeGL(int w, int h) override;
    virtual void paintGL() override;
};
