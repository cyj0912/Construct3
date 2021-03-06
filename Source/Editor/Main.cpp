#include <QApplication>
#include <QCommandLineParser>
#include <QProcess>
#include <QFileInfo>
#include <QMessageBox>
#include <QSurfaceFormat>
#include "MainWindow.h"
#include "EngineLoader.h"
#include "Editor.h"
#include <Core.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QApplication::setApplicationName("Editor");
    QApplication::setApplicationVersion("1.0");
#if C3_OS == C3_OS_WINDOWS_NT
	//Windows native theme looks so ugly
	app.setStyle("fusion");
#endif

    QCommandLineParser parser;
    parser.setApplicationDescription("The Editor");
    parser.addHelpOption();
    parser.addVersionOption();
    QCommandLineOption dataDirOption("root",
                                     "Root directory location.\nThis will override ENGINE_ROOT.",
                                     "path");
    parser.addOption(dataDirOption);
    parser.process(app);

    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    QString absPath;
    if(!parser.value(dataDirOption).isEmpty())
    {
        absPath = parser.value(dataDirOption);
    }
    else if(env.contains("ENGINE_ROOT"))
        absPath = env.value("ENGINE_ROOT");
    else
        absPath = ".";
    QFileInfo dirInfo(absPath);
    if(!dirInfo.exists() || !dirInfo.isDir() || !QFileInfo::exists(absPath + "/Data"))
    {
        const char* msg = "Invalid root directory!";
        QMessageBox::critical(nullptr, app.applicationName(), msg);
        throw msg;
    }
    absPath = dirInfo.canonicalFilePath();
    EngineLoader.SetRootDirectory(absPath.toUtf8().constData());

    c3::RC.Loader = &EngineLoader;
    c3::RC.Loader->InitEngine();

    c3::FEditor EditorController;
    c3::RC.Editor = &EditorController;

    QSurfaceFormat format;
    format.setVersion(4, 5);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setDepthBufferSize(24);
    format.setStencilBufferSize(8);
    QSurfaceFormat::setDefaultFormat(format);

    MainWindow mainWindow;
	c3::FLogDisplay* LogDisplay = static_cast<c3::FLogDisplay*>(EditorController.GetLogDisplay());
    QObject::connect(LogDisplay, &c3::FLogDisplay::LogRefreshed,
                     &mainWindow, &MainWindow::OnLogChanged);
	mainWindow.showMaximized();
    app.exec();
}
