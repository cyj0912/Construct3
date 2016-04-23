#include "Editor.h"
C3_NAMESPACE_BEGIN
void FLogDisplay::Refresh()
{
    emit LogRefreshed();
}

ILogDisplay* FEditor::GetLogDisplay()
{
    return &MainWindowLog;
}
C3_NAMESPACE_END
