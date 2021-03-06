#pragma once

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void on_actionExit_triggered();
	void on_actionReloadShader_triggered();
	void on_actionNearFar_triggered();
    void OnLogChanged();

private:
    Ui::MainWindow *ui;
};
