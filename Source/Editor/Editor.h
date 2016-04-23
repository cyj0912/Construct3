#pragma once
#include <Core.h>
#include <IEditor.h>
#include <QObject>
C3_NAMESPACE_BEGIN
class FLogDisplay : public QObject, public ILogDisplay
{
    Q_OBJECT
public:
    void Refresh() override;

signals:
    void LogRefreshed();
};

class FEditor : public IEditor
{
public:
    ILogDisplay* GetLogDisplay() override;

private:
    FLogDisplay MainWindowLog;
};
C3_NAMESPACE_END
