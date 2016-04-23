#pragma once
#include <Core.h>
C3_NAMESPACE_BEGIN
/*
 * TODO:
 * Prevent deletion and copying on these interfaces.
 */

class ILogDisplay
{
protected:
    ~ILogDisplay() {}
public:
    virtual void Refresh() = 0;
};

class IEditor
{
protected:
    ~IEditor() {}
public:
    virtual ILogDisplay* GetLogDisplay() = 0;
};
C3_NAMESPACE_END
