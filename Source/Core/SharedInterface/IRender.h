#pragma once
#include <Core.h>
C3_NAMESPACE_BEGIN
typedef void* (*GLLOADADDRESS)(const char *name);

class SGObject;
class IRender
{
public:
    enum class EFlag
    {
        ReloadShader,
        SwitchNearFar,
        NUMBEROFFLAGS
    };
    virtual void Init() = 0;
    virtual void Init(GLLOADADDRESS loader) = 0;
    virtual void Shutdown() = 0;
    virtual void PrepareGL() = 0;
    virtual void RenderOneFrame() = 0;
    virtual void RenderSprite() = 0;
    virtual void Resize(int w, int h) = 0;
    virtual void DrawControl(float x, float y, float w, float h) = 0;
    virtual void SetFlag(EFlag flag, bool value) = 0;
	virtual SGObject* NewSGObject() = 0;
};
C3_NAMESPACE_END
