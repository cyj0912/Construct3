#pragma once
#include <QOpenGLWindow>

class GLGameWindow : public QOpenGLWindow
{
public:
    GLGameWindow();

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override
    {
        QWindow::keyReleaseEvent(event);
    }
    void mousePressEvent(QMouseEvent *event) override
    {
        QWindow::mousePressEvent(event);
    }
    void mouseReleaseEvent(QMouseEvent *event) override
    {
        QWindow::mouseReleaseEvent(event);
    }
    void mouseDoubleClickEvent(QMouseEvent *event) override
    {
        QWindow::mouseDoubleClickEvent(event);
    }
    void mouseMoveEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override
    {
        QWindow::wheelEvent(event);
    }
};
